#include "AsyncDocumentLoader.h"
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QMutexLocker>

AsyncDocumentLoader::AsyncDocumentLoader(QObject* parent)
    : QObject(parent)
    , m_state(LoadingState::Idle)
    , m_currentProgress(0)
    , m_expectedLoadTime(0)
    , m_startTime(0)
    , m_workerThread(nullptr)
    , m_worker(nullptr)
{
    // 初始化进度定时器
    m_progressTimer = new QTimer(this);
    m_progressTimer->setInterval(PROGRESS_UPDATE_INTERVAL);
    connect(m_progressTimer, &QTimer::timeout, this, &AsyncDocumentLoader::onProgressTimerTimeout);
}

AsyncDocumentLoader::~AsyncDocumentLoader()
{
    cancelLoading();
}

void AsyncDocumentLoader::loadDocument(const QString& filePath)
{
    QMutexLocker locker(&m_stateMutex);
    
    // 检查文件是否存在
    if (!QFile::exists(filePath)) {
        emit loadingFailed("文件不存在", filePath);
        return;
    }
    
    // 如果正在加载，先取消
    if (m_state == LoadingState::Loading) {
        cancelLoading();
    }
    
    // 重置状态
    resetState();
    m_state = LoadingState::Loading;
    m_currentFilePath = filePath;
    
    locker.unlock();
    
    // 计算预期加载时间
    QFileInfo fileInfo(filePath);
    qint64 fileSize = fileInfo.size();
    m_expectedLoadTime = calculateExpectedLoadTime(fileSize);
    
    emit loadingMessageChanged(QString("正在加载 %1...").arg(fileInfo.fileName()));
    emit loadingProgressChanged(0);
    
    // 创建工作线程
    m_workerThread = new QThread(this);
    m_worker = new AsyncDocumentLoaderWorker(filePath);
    m_worker->moveToThread(m_workerThread);
    
    // 连接信号
    connect(m_workerThread, &QThread::started, m_worker, &AsyncDocumentLoaderWorker::doLoad);
    connect(m_worker, &AsyncDocumentLoaderWorker::loadCompleted, this, [this](Poppler::Document* document) {
        QMutexLocker locker(&m_stateMutex);
        if (m_state == LoadingState::Loading) {
            m_state = LoadingState::Completed;
            QString filePath = m_currentFilePath;
            locker.unlock();

            stopProgressSimulation();
            emit loadingProgressChanged(100);
            emit loadingMessageChanged("加载完成");
            emit documentLoaded(document, filePath);

            // 清理工作线程
            if (m_workerThread) {
                m_workerThread->quit();
                m_workerThread->wait();
                m_workerThread->deleteLater();
                m_workerThread = nullptr;
            }
            if (m_worker) {
                m_worker->deleteLater();
                m_worker = nullptr;
            }
        }
    });
    connect(m_worker, &AsyncDocumentLoaderWorker::loadFailed, this, [this](const QString& error) {
        QMutexLocker locker(&m_stateMutex);
        if (m_state == LoadingState::Loading) {
            m_state = LoadingState::Failed;
            locker.unlock();
            stopProgressSimulation();
            emit loadingFailed(error, m_currentFilePath);
        }
    });
    
    // 开始进度模拟和加载
    startProgressSimulation();
    m_workerThread->start();
}

void AsyncDocumentLoader::cancelLoading()
{
    QMutexLocker locker(&m_stateMutex);
    
    if (m_state != LoadingState::Loading) {
        return;
    }
    
    m_state = LoadingState::Cancelled;
    QString filePath = m_currentFilePath;
    
    locker.unlock();
    
    stopProgressSimulation();
    
    // 清理工作线程
    if (m_workerThread) {
        m_workerThread->quit();
        if (!m_workerThread->wait(3000)) {
            m_workerThread->terminate();
            m_workerThread->wait(1000);
        }
        m_workerThread->deleteLater();
        m_workerThread = nullptr;
    }
    
    if (m_worker) {
        m_worker->deleteLater();
        m_worker = nullptr;
    }
    
    emit loadingCancelled(filePath);
}

AsyncDocumentLoader::LoadingState AsyncDocumentLoader::currentState() const
{
    QMutexLocker locker(&m_stateMutex);
    return m_state;
}

QString AsyncDocumentLoader::currentFilePath() const
{
    QMutexLocker locker(&m_stateMutex);
    return m_currentFilePath;
}

void AsyncDocumentLoader::onProgressTimerTimeout()
{
    QMutexLocker locker(&m_stateMutex);
    
    if (m_state != LoadingState::Loading) {
        return;
    }
    
    locker.unlock();
    
    // 计算当前进度
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = currentTime - m_startTime;
    
    // 使用非线性进度计算，前80%较快，后20%较慢
    int newProgress;
    if (elapsed < m_expectedLoadTime * 0.8) {
        newProgress = static_cast<int>((elapsed * 80.0) / (m_expectedLoadTime * 0.8));
    } else {
        int baseProgress = 80;
        qint64 remainingTime = elapsed - static_cast<qint64>(m_expectedLoadTime * 0.8);
        qint64 slowPhaseTime = static_cast<qint64>(m_expectedLoadTime * 0.2);
        int additionalProgress = static_cast<int>((remainingTime * 15.0) / slowPhaseTime); // 最多到95%
        newProgress = qMin(95, baseProgress + additionalProgress);
    }
    
    if (newProgress != m_currentProgress) {
        m_currentProgress = newProgress;
        emit loadingProgressChanged(m_currentProgress);
    }
}



void AsyncDocumentLoader::startProgressSimulation()
{
    m_currentProgress = 0;
    m_startTime = QDateTime::currentMSecsSinceEpoch();
    m_progressTimer->start();
}

void AsyncDocumentLoader::stopProgressSimulation()
{
    m_progressTimer->stop();
}

void AsyncDocumentLoader::resetState()
{
    m_currentProgress = 0;
    m_expectedLoadTime = 0;
    m_startTime = 0;
    m_currentFilePath.clear();
}

int AsyncDocumentLoader::calculateExpectedLoadTime(qint64 fileSize) const
{
    if (fileSize < SIZE_THRESHOLD_FAST) {
        return MIN_LOAD_TIME;
    } else if (fileSize < SIZE_THRESHOLD_MEDIUM) {
        // 1MB到10MB之间线性增长
        double ratio = static_cast<double>(fileSize - SIZE_THRESHOLD_FAST) / 
                      (SIZE_THRESHOLD_MEDIUM - SIZE_THRESHOLD_FAST);
        return MIN_LOAD_TIME + static_cast<int>(ratio * (MAX_LOAD_TIME - MIN_LOAD_TIME) * 0.6);
    } else {
        // 大于10MB的文件
        return static_cast<int>(MAX_LOAD_TIME * 0.8);
    }
}

// AsyncDocumentLoaderWorker 实现
AsyncDocumentLoaderWorker::AsyncDocumentLoaderWorker(const QString& filePath)
    : m_filePath(filePath)
{
}

void AsyncDocumentLoaderWorker::doLoad()
{
    try {
        // 实际加载文档
        auto document = Poppler::Document::load(m_filePath);
        if (!document) {
            emit loadFailed("无法加载PDF文档");
            return;
        }
        
        // 配置文档渲染设置
        document->setRenderHint(Poppler::Document::Antialiasing, true);
        document->setRenderHint(Poppler::Document::TextAntialiasing, true);
        document->setRenderHint(Poppler::Document::TextHinting, true);
        document->setRenderHint(Poppler::Document::TextSlightHinting, true);
        document->setRenderHint(Poppler::Document::ThinLineShape, true);
        document->setRenderHint(Poppler::Document::OverprintPreview, true);
        
        // 验证文档
        if (document->numPages() <= 0) {
            emit loadFailed("文档没有有效页面");
            return;
        }
        
        // 测试第一页
        std::unique_ptr<Poppler::Page> testPage(document->page(0));
        if (!testPage) {
            emit loadFailed("无法访问文档页面");
            return;
        }
        
        emit loadCompleted(document.release());
        
    } catch (const std::exception& e) {
        emit loadFailed(QString("加载异常: %1").arg(e.what()));
    } catch (...) {
        emit loadFailed("未知加载错误");
    }
}


