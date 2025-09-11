// Test file to verify clangd configuration for Qt constants
// This file should not show "missing-includes" warnings after clangd restart

#include <QPainter>
#include <QPixmap>
#include <QColor>

void testQtConstants() {
    QPixmap pixmap(100, 100);
    QPainter painter(&pixmap);
    
    // These Qt constants should not trigger missing-includes warnings:
    painter.setPen(Qt::white);           // Qt::white
    painter.setBrush(Qt::transparent);   // Qt::transparent
    painter.fillRect(pixmap.rect(), Qt::black);  // Qt::black
    
    // Alignment constants
    painter.drawText(pixmap.rect(), Qt::AlignCenter, "Test");     // Qt::AlignCenter
    painter.drawText(pixmap.rect(), Qt::AlignLeft, "Left");       // Qt::AlignLeft
    painter.drawText(pixmap.rect(), Qt::AlignRight, "Right");     // Qt::AlignRight
    
    // Other common Qt constants
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

// Test Qt enums and flags
void testQtEnums() {
    Qt::WindowFlags flags = Qt::Window | Qt::WindowTitleHint;
    Qt::Alignment align = Qt::AlignCenter | Qt::AlignVCenter;
    Qt::PenStyle style = Qt::SolidLine;
    Qt::BrushStyle brushStyle = Qt::NoBrush;
    
    // These should all work without missing-includes warnings
    (void)flags;
    (void)align;
    (void)style;
    (void)brushStyle;
}
