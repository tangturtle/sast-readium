#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QFileInfo>
#include <QMutex>

#include <poppler/qt6/poppler-qt6.h>

// 前向声明
class AsyncDocumentLoaderWorker;

/**
 * 异步文档加载器
 * 在后台线程中加载PDF文档，避免阻塞UI线程
 * 提供加载进度回调和取消功能
 */
class AsyncDocumentLoader : public QObject
{
    Q_OBJECT

public:
    enum class LoadingState {
        Idle,           // 空闲状态
        Loading,        // 正在加载
        Completed,      // 加载完成
        Failed,         // 加载失败
        Cancelled       // 加载取消
    };

    explicit AsyncDocumentLoader(QObject* parent = nullptr);
    ~AsyncDocumentLoader();

    // 开始异步加载文档
    void loadDocument(const QString& filePath);
    
    // 取消当前加载
    void cancelLoading();
    
    // 获取当前状态
    LoadingState currentState() const;
    
    // 获取当前加载的文件路径
    QString currentFilePath() const;

signals:
    // 加载进度更新 (0-100)
    void loadingProgressChanged(int progress);
    
    // 加载状态消息更新
    void loadingMessageChanged(const QString& message);
    
    // 加载完成
    void documentLoaded(Poppler::Document* document, const QString& filePath);
    
    // 加载失败
    void loadingFailed(const QString& error, const QString& filePath);
    
    // 加载取消
    void loadingCancelled(const QString& filePath);

private slots:
    void onProgressTimerTimeout();

private:

    void startProgressSimulation();
    void stopProgressSimulation();
    void resetState();
    int calculateExpectedLoadTime(qint64 fileSize) const;

    // 状态管理
    LoadingState m_state;
    QString m_currentFilePath;
    mutable QMutex m_stateMutex;
    
    // 进度模拟
    QTimer* m_progressTimer;
    int m_currentProgress;
    int m_expectedLoadTime; // 预期加载时间(ms)
    qint64 m_startTime;     // 开始加载时间
    
    // 工作线程
    QThread* m_workerThread;
    AsyncDocumentLoaderWorker* m_worker;
    
    // 常量
    static constexpr int PROGRESS_UPDATE_INTERVAL = 50; // 50ms更新一次进度
    static constexpr int MIN_LOAD_TIME = 200;           // 最小加载时间200ms
    static constexpr int MAX_LOAD_TIME = 5000;          // 最大加载时间5s
    static constexpr qint64 SIZE_THRESHOLD_FAST = 1024 * 1024;      // 1MB以下快速加载
    static constexpr qint64 SIZE_THRESHOLD_MEDIUM = 10 * 1024 * 1024; // 10MB以下中等加载
};

/**
 * 文档加载工作线程类
 */
class AsyncDocumentLoaderWorker : public QObject
{
    Q_OBJECT

public:
    AsyncDocumentLoaderWorker(const QString& filePath);

public slots:
    void doLoad();

signals:
    void loadCompleted(Poppler::Document* document);
    void loadFailed(const QString& error);

private:
    QString m_filePath;
};
