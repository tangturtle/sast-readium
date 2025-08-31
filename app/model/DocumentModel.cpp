#include "DocumentModel.h"
#include <QFileInfo>

DocumentModel::DocumentModel() : currentDocumentIndex(-1) {
    // 初始化异步加载器
    asyncLoader = new AsyncDocumentLoader(this);

    // 连接异步加载器信号
    connect(asyncLoader, &AsyncDocumentLoader::loadingProgressChanged,
            this, &DocumentModel::loadingProgressChanged);
    connect(asyncLoader, &AsyncDocumentLoader::loadingMessageChanged,
            this, &DocumentModel::loadingMessageChanged);
    connect(asyncLoader, &AsyncDocumentLoader::documentLoaded,
            this, &DocumentModel::onDocumentLoaded);
    connect(asyncLoader, &AsyncDocumentLoader::loadingFailed,
            this, &DocumentModel::loadingFailed);
}

bool DocumentModel::openFromFile(const QString& filePath) {
    if (filePath.isEmpty() || !QFile::exists(filePath)) {
        qWarning() << "Invalid file path:" << filePath;
        emit loadingFailed("文件路径无效", filePath);
        return false;
    }

    // 检查文档是否已经打开
    for (size_t i = 0; i < documents.size(); ++i) {
        if (documents[i]->filePath == filePath) {
            switchToDocument(static_cast<int>(i));
            return true;
        }
    }

    // 发送加载开始信号
    emit loadingStarted(filePath);

    // 使用异步加载器加载文档
    asyncLoader->loadDocument(filePath);

    return true; // 异步加载，立即返回true
}

void DocumentModel::onDocumentLoaded(Poppler::Document* document, const QString& filePath)
{
    if (!document) {
        emit loadingFailed("文档加载失败", filePath);
        return;
    }

    // 创建unique_ptr管理文档
    std::unique_ptr<Poppler::Document> popplerDoc(document);

    // 创建文档信息
    auto docInfo = std::make_unique<DocumentInfo>(filePath, std::move(popplerDoc));
    documents.push_back(std::move(docInfo));

    int newIndex = static_cast<int>(documents.size() - 1);
    currentDocumentIndex = newIndex;

    qDebug() << "Async loaded successfully:" << filePath;
    emit documentOpened(newIndex, documents[newIndex]->fileName);
    emit currentDocumentChanged(newIndex);
}

bool DocumentModel::closeDocument(int index) {
    if (!isValidIndex(index)) {
        return false;
    }

    documents.erase(documents.begin() + index);
    emit documentClosed(index);

    // 调整当前文档索引
    if (documents.empty()) {
        currentDocumentIndex = -1;
        emit allDocumentsClosed();
    } else if (index <= currentDocumentIndex) {
        if (currentDocumentIndex >= static_cast<int>(documents.size())) {
            currentDocumentIndex = static_cast<int>(documents.size()) - 1;
        }
        emit currentDocumentChanged(currentDocumentIndex);
    }

    return true;
}

bool DocumentModel::closeCurrentDocument() {
    return closeDocument(currentDocumentIndex);
}

void DocumentModel::switchToDocument(int index) {
    if (isValidIndex(index) && index != currentDocumentIndex) {
        currentDocumentIndex = index;
        emit currentDocumentChanged(index);
    }
}

int DocumentModel::getDocumentCount() const {
    return static_cast<int>(documents.size());
}

int DocumentModel::getCurrentDocumentIndex() const {
    return currentDocumentIndex;
}

QString DocumentModel::getCurrentFilePath() const {
    if (isValidIndex(currentDocumentIndex)) {
        return documents[currentDocumentIndex]->filePath;
    }
    return QString();
}

QString DocumentModel::getCurrentFileName() const {
    if (isValidIndex(currentDocumentIndex)) {
        return documents[currentDocumentIndex]->fileName;
    }
    return QString();
}

QString DocumentModel::getDocumentFileName(int index) const {
    if (isValidIndex(index)) {
        return documents[index]->fileName;
    }
    return QString();
}

QString DocumentModel::getDocumentFilePath(int index) const {
    if (isValidIndex(index)) {
        return documents[index]->filePath;
    }
    return QString();
}

Poppler::Document* DocumentModel::getCurrentDocument() const {
    if (isValidIndex(currentDocumentIndex)) {
        return documents[currentDocumentIndex]->document.get();
    }
    return nullptr;
}

Poppler::Document* DocumentModel::getDocument(int index) const {
    if (isValidIndex(index)) {
        return documents[index]->document.get();
    }
    return nullptr;
}

bool DocumentModel::isEmpty() const {
    return documents.empty();
}

bool DocumentModel::isValidIndex(int index) const {
    return index >= 0 && index < static_cast<int>(documents.size());
}
