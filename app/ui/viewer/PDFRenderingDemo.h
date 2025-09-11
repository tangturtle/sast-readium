#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QSlider>
#include <QSpinBox>
#include "PDFViewer.h"

/**
 * Demo widget to showcase QGraphics PDF rendering capabilities
 * This widget provides controls to switch between traditional and QGraphics rendering modes
 */
class PDFRenderingDemo : public QWidget
{
    Q_OBJECT

public:
    explicit PDFRenderingDemo(QWidget* parent = nullptr);
    
    void setPDFViewer(PDFViewer* viewer);
    
private slots:
    void onRenderingModeChanged();
    void onHighQualityToggled(bool enabled);
    void onViewModeChanged(int index);
    void onPageSpacingChanged(int spacing);
    void onPageMarginChanged(int margin);
    void onSmoothScrollingToggled(bool enabled);
    void resetToDefaults();
    
private:
    void setupUI();
    void updateControlsVisibility();
    
    PDFViewer* m_pdfViewer;
    
    // Controls
    QGroupBox* m_renderingGroup;
    QCheckBox* m_enableQGraphicsCheck;
    QCheckBox* m_highQualityCheck;
    QCheckBox* m_smoothScrollingCheck;
    
    QGroupBox* m_viewGroup;
    QComboBox* m_viewModeCombo;
    QSlider* m_pageSpacingSlider;
    QSlider* m_pageMarginSlider;
    QSpinBox* m_pageSpacingSpin;
    QSpinBox* m_pageMarginSpin;
    
    QGroupBox* m_infoGroup;
    QLabel* m_renderingModeLabel;
    QLabel* m_performanceLabel;
    
    QPushButton* m_resetButton;
};

/**
 * Enhanced PDF viewer widget that integrates both traditional and QGraphics rendering
 * This provides a unified interface for PDF viewing with optional QGraphics enhancements
 */
class EnhancedPDFViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit EnhancedPDFViewer(QWidget* parent = nullptr);
    
    // Document management
    void setDocument(Poppler::Document* document);
    void clearDocument();
    
    // Rendering mode control
    void setQGraphicsRenderingEnabled(bool enabled);
    bool isQGraphicsRenderingEnabled() const;
    
    // Enhanced features (available when QGraphics is enabled)
    void setHighQualityRendering(bool enabled);
    void setViewMode(int mode);
    void setPageSpacing(int spacing);
    void setPageMargin(int margin);
    void setSmoothScrolling(bool enabled);
    
    // Navigation (unified interface)
    void goToPage(int pageNumber);
    void nextPage();
    void previousPage();
    void firstPage();
    void lastPage();
    
    // Zoom operations (unified interface)
    void zoomIn();
    void zoomOut();
    void zoomToFit();
    void zoomToWidth();
    void zoomToHeight();
    void setZoom(double factor);
    void resetZoom();
    
    // Rotation (unified interface)
    void rotateLeft();
    void rotateRight();
    void resetRotation();
    void setRotation(int degrees);
    
    // Getters
    int getCurrentPage() const;
    double getZoomFactor() const;
    int getRotation() const;
    int getPageCount() const;
    bool hasDocument() const;
    
signals:
    void documentChanged(bool hasDocument);
    void currentPageChanged(int pageNumber);
    void zoomChanged(double factor);
    void rotationChanged(int degrees);
    void renderingModeChanged(bool qgraphicsEnabled);
    
private slots:
    void onPDFViewerPageChanged(int pageNumber);
    void onPDFViewerZoomChanged(double factor);
    void onPDFViewerRotationChanged(int degrees);
    void onPDFViewerDocumentChanged(bool hasDocument);
    
private:
    void setupUI();
    void connectSignals();
    void updateRenderingMode();
    
    PDFViewer* m_pdfViewer;
    PDFRenderingDemo* m_demoControls;
    
    bool m_qgraphicsEnabled;
    bool m_showDemoControls;
};

#ifdef ENABLE_QGRAPHICS_PDF_SUPPORT

/**
 * Utility class for managing PDF rendering performance
 * Provides metrics and optimization suggestions for both rendering modes
 */
class PDFRenderingPerformanceManager : public QObject
{
    Q_OBJECT
    
public:
    struct RenderingMetrics {
        double averageRenderTime;
        double memoryUsage;
        int cacheHitRate;
        int totalPagesRendered;
        QString recommendedMode;
    };
    
    explicit PDFRenderingPerformanceManager(QObject* parent = nullptr);
    
    void startMeasurement();
    void recordRenderTime(double timeMs);
    void recordMemoryUsage(double memoryMB);
    void recordCacheHit(bool hit);
    
    RenderingMetrics getMetrics() const;
    QString getRecommendation() const;
    void reset();
    
signals:
    void metricsUpdated(const RenderingMetrics& metrics);
    
private:
    void updateRecommendation();
    
    QList<double> m_renderTimes;
    QList<double> m_memoryUsages;
    int m_cacheHits;
    int m_cacheMisses;
    int m_totalPages;
    QString m_currentRecommendation;
    QTimer* m_updateTimer;
};

#endif // ENABLE_QGRAPHICS_PDF_SUPPORT
