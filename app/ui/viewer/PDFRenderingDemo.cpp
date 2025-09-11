#include "PDFRenderingDemo.h"
#include <QGridLayout>
#include <QSplitter>
#include <QTimer>
#include <QDebug>

// PDFRenderingDemo Implementation
PDFRenderingDemo::PDFRenderingDemo(QWidget* parent)
    : QWidget(parent)
    , m_pdfViewer(nullptr)
{
    setupUI();
}

void PDFRenderingDemo::setPDFViewer(PDFViewer* viewer)
{
    m_pdfViewer = viewer;
    updateControlsVisibility();
}

void PDFRenderingDemo::setupUI()
{
    setWindowTitle("PDF Rendering Demo Controls");
    setMinimumSize(300, 400);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Rendering Mode Group
    m_renderingGroup = new QGroupBox("Rendering Mode", this);
    QVBoxLayout* renderingLayout = new QVBoxLayout(m_renderingGroup);
    
    m_enableQGraphicsCheck = new QCheckBox("Enable QGraphics Rendering", this);
    m_highQualityCheck = new QCheckBox("High Quality Rendering", this);
    m_smoothScrollingCheck = new QCheckBox("Smooth Scrolling", this);
    
    renderingLayout->addWidget(m_enableQGraphicsCheck);
    renderingLayout->addWidget(m_highQualityCheck);
    renderingLayout->addWidget(m_smoothScrollingCheck);
    
    // View Mode Group
    m_viewGroup = new QGroupBox("View Settings", this);
    QGridLayout* viewLayout = new QGridLayout(m_viewGroup);
    
    viewLayout->addWidget(new QLabel("View Mode:"), 0, 0);
    m_viewModeCombo = new QComboBox(this);
    m_viewModeCombo->addItems({"Single Page", "Continuous Page", "Facing Pages", "Continuous Facing"});
    viewLayout->addWidget(m_viewModeCombo, 0, 1);
    
    viewLayout->addWidget(new QLabel("Page Spacing:"), 1, 0);
    m_pageSpacingSlider = new QSlider(Qt::Horizontal, this);
    m_pageSpacingSlider->setRange(0, 50);
    m_pageSpacingSlider->setValue(20);
    m_pageSpacingSpin = new QSpinBox(this);
    m_pageSpacingSpin->setRange(0, 50);
    m_pageSpacingSpin->setValue(20);
    viewLayout->addWidget(m_pageSpacingSlider, 1, 1);
    viewLayout->addWidget(m_pageSpacingSpin, 1, 2);
    
    viewLayout->addWidget(new QLabel("Page Margin:"), 2, 0);
    m_pageMarginSlider = new QSlider(Qt::Horizontal, this);
    m_pageMarginSlider->setRange(10, 100);
    m_pageMarginSlider->setValue(50);
    m_pageMarginSpin = new QSpinBox(this);
    m_pageMarginSpin->setRange(10, 100);
    m_pageMarginSpin->setValue(50);
    viewLayout->addWidget(m_pageMarginSlider, 2, 1);
    viewLayout->addWidget(m_pageMarginSpin, 2, 2);
    
    // Info Group
    m_infoGroup = new QGroupBox("Information", this);
    QVBoxLayout* infoLayout = new QVBoxLayout(m_infoGroup);
    
    m_renderingModeLabel = new QLabel("Current Mode: Traditional", this);
    m_performanceLabel = new QLabel("Performance: N/A", this);
    
    infoLayout->addWidget(m_renderingModeLabel);
    infoLayout->addWidget(m_performanceLabel);
    
    // Reset Button
    m_resetButton = new QPushButton("Reset to Defaults", this);
    
    // Add to main layout
    mainLayout->addWidget(m_renderingGroup);
    mainLayout->addWidget(m_viewGroup);
    mainLayout->addWidget(m_infoGroup);
    mainLayout->addWidget(m_resetButton);
    mainLayout->addStretch();
    
    // Connect signals
    connect(m_enableQGraphicsCheck, &QCheckBox::toggled, this, &PDFRenderingDemo::onRenderingModeChanged);
    connect(m_highQualityCheck, &QCheckBox::toggled, this, &PDFRenderingDemo::onHighQualityToggled);
    connect(m_smoothScrollingCheck, &QCheckBox::toggled, this, &PDFRenderingDemo::onSmoothScrollingToggled);
    connect(m_viewModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PDFRenderingDemo::onViewModeChanged);
    
    connect(m_pageSpacingSlider, &QSlider::valueChanged, m_pageSpacingSpin, &QSpinBox::setValue);
    connect(m_pageSpacingSpin, QOverload<int>::of(&QSpinBox::valueChanged), m_pageSpacingSlider, &QSlider::setValue);
    connect(m_pageSpacingSlider, &QSlider::valueChanged, this, &PDFRenderingDemo::onPageSpacingChanged);
    
    connect(m_pageMarginSlider, &QSlider::valueChanged, m_pageMarginSpin, &QSpinBox::setValue);
    connect(m_pageMarginSpin, QOverload<int>::of(&QSpinBox::valueChanged), m_pageMarginSlider, &QSlider::setValue);
    connect(m_pageMarginSlider, &QSlider::valueChanged, this, &PDFRenderingDemo::onPageMarginChanged);
    
    connect(m_resetButton, &QPushButton::clicked, this, &PDFRenderingDemo::resetToDefaults);
    
    updateControlsVisibility();
}

void PDFRenderingDemo::updateControlsVisibility()
{
#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT
    bool qgraphicsAvailable = true;
#else
    bool qgraphicsAvailable = false;
#endif
    
    m_enableQGraphicsCheck->setEnabled(qgraphicsAvailable);
    if (!qgraphicsAvailable) {
        m_enableQGraphicsCheck->setToolTip("QGraphics support not compiled in");
        m_enableQGraphicsCheck->setChecked(false);
    }
    
    bool qgraphicsEnabled = m_enableQGraphicsCheck->isChecked() && qgraphicsAvailable;
    m_highQualityCheck->setEnabled(qgraphicsEnabled);
    m_smoothScrollingCheck->setEnabled(qgraphicsEnabled);
    m_viewModeCombo->setEnabled(qgraphicsEnabled);
    m_pageSpacingSlider->setEnabled(qgraphicsEnabled);
    m_pageSpacingSpin->setEnabled(qgraphicsEnabled);
    m_pageMarginSlider->setEnabled(qgraphicsEnabled);
    m_pageMarginSpin->setEnabled(qgraphicsEnabled);
    
    QString mode = qgraphicsEnabled ? "QGraphics Enhanced" : "Traditional";
    m_renderingModeLabel->setText(QString("Current Mode: %1").arg(mode));
}

void PDFRenderingDemo::onRenderingModeChanged()
{
#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT
    if (m_pdfViewer) {
        bool enabled = m_enableQGraphicsCheck->isChecked();
        m_pdfViewer->setQGraphicsRenderingEnabled(enabled);
        
        if (enabled) {
            // Apply current settings
            m_pdfViewer->setQGraphicsHighQualityRendering(m_highQualityCheck->isChecked());
            m_pdfViewer->setQGraphicsViewMode(m_viewModeCombo->currentIndex());
        }
    }
#endif
    updateControlsVisibility();
}

void PDFRenderingDemo::onHighQualityToggled(bool enabled)
{
#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT
    if (m_pdfViewer && m_enableQGraphicsCheck->isChecked()) {
        m_pdfViewer->setQGraphicsHighQualityRendering(enabled);
    }
#endif
}

void PDFRenderingDemo::onViewModeChanged(int index)
{
#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT
    if (m_pdfViewer && m_enableQGraphicsCheck->isChecked()) {
        m_pdfViewer->setQGraphicsViewMode(index);
    }
#endif
}

void PDFRenderingDemo::onPageSpacingChanged(int spacing)
{
    Q_UNUSED(spacing)
    // This would be implemented when QGraphics viewer supports page spacing
}

void PDFRenderingDemo::onPageMarginChanged(int margin)
{
    Q_UNUSED(margin)
    // This would be implemented when QGraphics viewer supports page margins
}

void PDFRenderingDemo::onSmoothScrollingToggled(bool enabled)
{
    Q_UNUSED(enabled)
    // This would be implemented when QGraphics viewer supports smooth scrolling setting
}

void PDFRenderingDemo::resetToDefaults()
{
    m_enableQGraphicsCheck->setChecked(false);
    m_highQualityCheck->setChecked(true);
    m_smoothScrollingCheck->setChecked(true);
    m_viewModeCombo->setCurrentIndex(0);
    m_pageSpacingSlider->setValue(20);
    m_pageMarginSlider->setValue(50);
}

// EnhancedPDFViewer Implementation
EnhancedPDFViewer::EnhancedPDFViewer(QWidget* parent)
    : QWidget(parent)
    , m_pdfViewer(nullptr)
    , m_demoControls(nullptr)
    , m_qgraphicsEnabled(false)
    , m_showDemoControls(true)
{
    setupUI();
    connectSignals();
}

void EnhancedPDFViewer::setupUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    
    // Create splitter for resizable layout
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    
    // Create PDF viewer
    m_pdfViewer = new PDFViewer(this);
    splitter->addWidget(m_pdfViewer);
    
    // Create demo controls
    if (m_showDemoControls) {
        m_demoControls = new PDFRenderingDemo(this);
        m_demoControls->setPDFViewer(m_pdfViewer);
        splitter->addWidget(m_demoControls);
        
        // Set initial sizes (PDF viewer gets more space)
        splitter->setSizes({700, 300});
    }
    
    mainLayout->addWidget(splitter);
}

void EnhancedPDFViewer::connectSignals()
{
    if (m_pdfViewer) {
        connect(m_pdfViewer, &PDFViewer::pageChanged, this, &EnhancedPDFViewer::onPDFViewerPageChanged);
        connect(m_pdfViewer, &PDFViewer::zoomChanged, this, &EnhancedPDFViewer::onPDFViewerZoomChanged);
        connect(m_pdfViewer, &PDFViewer::rotationChanged, this, &EnhancedPDFViewer::onPDFViewerRotationChanged);
        connect(m_pdfViewer, &PDFViewer::documentChanged, this, &EnhancedPDFViewer::onPDFViewerDocumentChanged);
    }
}

void EnhancedPDFViewer::setDocument(Poppler::Document* document)
{
    if (m_pdfViewer) {
        m_pdfViewer->setDocument(document);
    }
}

void EnhancedPDFViewer::clearDocument()
{
    if (m_pdfViewer) {
        m_pdfViewer->clearDocument();
    }
}

void EnhancedPDFViewer::setQGraphicsRenderingEnabled(bool enabled)
{
#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT
    if (m_pdfViewer && m_qgraphicsEnabled != enabled) {
        m_qgraphicsEnabled = enabled;
        m_pdfViewer->setQGraphicsRenderingEnabled(enabled);
        emit renderingModeChanged(enabled);
    }
#else
    Q_UNUSED(enabled)
#endif
}

bool EnhancedPDFViewer::isQGraphicsRenderingEnabled() const
{
#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT
    return m_qgraphicsEnabled;
#else
    return false;
#endif
}

// Unified interface methods - these delegate to the PDF viewer
void EnhancedPDFViewer::goToPage(int pageNumber)
{
    if (m_pdfViewer) m_pdfViewer->goToPage(pageNumber);
}

void EnhancedPDFViewer::nextPage()
{
    if (m_pdfViewer) m_pdfViewer->nextPage();
}

void EnhancedPDFViewer::previousPage()
{
    if (m_pdfViewer) m_pdfViewer->previousPage();
}

void EnhancedPDFViewer::zoomIn()
{
    if (m_pdfViewer) m_pdfViewer->zoomIn();
}

void EnhancedPDFViewer::zoomOut()
{
    if (m_pdfViewer) m_pdfViewer->zoomOut();
}

int EnhancedPDFViewer::getCurrentPage() const
{
    return m_pdfViewer ? m_pdfViewer->getCurrentPage() : -1;
}

double EnhancedPDFViewer::getZoomFactor() const
{
    return m_pdfViewer ? m_pdfViewer->getCurrentZoom() : 1.0;
}

bool EnhancedPDFViewer::hasDocument() const
{
    return m_pdfViewer ? m_pdfViewer->hasDocument() : false;
}

// Signal forwarding
void EnhancedPDFViewer::onPDFViewerPageChanged(int pageNumber)
{
    emit currentPageChanged(pageNumber);
}

void EnhancedPDFViewer::onPDFViewerZoomChanged(double factor)
{
    emit zoomChanged(factor);
}

void EnhancedPDFViewer::onPDFViewerRotationChanged(int degrees)
{
    emit rotationChanged(degrees);
}

void EnhancedPDFViewer::onPDFViewerDocumentChanged(bool hasDocument)
{
    emit documentChanged(hasDocument);
}

#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT

// PDFRenderingPerformanceManager Implementation
PDFRenderingPerformanceManager::PDFRenderingPerformanceManager(QObject* parent)
    : QObject(parent)
    , m_cacheHits(0)
    , m_cacheMisses(0)
    , m_totalPages(0)
    , m_currentRecommendation("Traditional")
{
    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(1000); // Update every second
    connect(m_updateTimer, &QTimer::timeout, this, &PDFRenderingPerformanceManager::updateRecommendation);
}

void PDFRenderingPerformanceManager::startMeasurement()
{
    reset();
    m_updateTimer->start();
}

void PDFRenderingPerformanceManager::recordRenderTime(double timeMs)
{
    m_renderTimes.append(timeMs);
    if (m_renderTimes.size() > 100) {
        m_renderTimes.removeFirst(); // Keep only last 100 measurements
    }
}

void PDFRenderingPerformanceManager::recordMemoryUsage(double memoryMB)
{
    m_memoryUsages.append(memoryMB);
    if (m_memoryUsages.size() > 100) {
        m_memoryUsages.removeFirst(); // Keep only last 100 measurements
    }
}

void PDFRenderingPerformanceManager::recordCacheHit(bool hit)
{
    if (hit) {
        m_cacheHits++;
    } else {
        m_cacheMisses++;
    }
}

PDFRenderingPerformanceManager::RenderingMetrics PDFRenderingPerformanceManager::getMetrics() const
{
    RenderingMetrics metrics;

    // Calculate average render time
    if (!m_renderTimes.isEmpty()) {
        double sum = 0;
        for (double time : m_renderTimes) {
            sum += time;
        }
        metrics.averageRenderTime = sum / m_renderTimes.size();
    } else {
        metrics.averageRenderTime = 0.0;
    }

    // Calculate average memory usage
    if (!m_memoryUsages.isEmpty()) {
        double sum = 0;
        for (double memory : m_memoryUsages) {
            sum += memory;
        }
        metrics.memoryUsage = sum / m_memoryUsages.size();
    } else {
        metrics.memoryUsage = 0.0;
    }

    // Calculate cache hit rate
    int totalCacheAccess = m_cacheHits + m_cacheMisses;
    if (totalCacheAccess > 0) {
        metrics.cacheHitRate = (m_cacheHits * 100) / totalCacheAccess;
    } else {
        metrics.cacheHitRate = 0;
    }

    metrics.totalPagesRendered = m_totalPages;
    metrics.recommendedMode = m_currentRecommendation;

    return metrics;
}

QString PDFRenderingPerformanceManager::getRecommendation() const
{
    return m_currentRecommendation;
}

void PDFRenderingPerformanceManager::reset()
{
    m_renderTimes.clear();
    m_memoryUsages.clear();
    m_cacheHits = 0;
    m_cacheMisses = 0;
    m_totalPages = 0;
    m_currentRecommendation = "Traditional";
}

void PDFRenderingPerformanceManager::updateRecommendation()
{
    RenderingMetrics metrics = getMetrics();

    // Simple recommendation logic
    if (metrics.averageRenderTime > 100.0 && metrics.memoryUsage < 200.0) {
        m_currentRecommendation = "QGraphics";
    } else if (metrics.memoryUsage > 500.0) {
        m_currentRecommendation = "Traditional";
    } else {
        m_currentRecommendation = "Balanced";
    }

    emit metricsUpdated(metrics);
}

#endif // ENABLE_QGRAPHICS_PDF_SUPPORT

