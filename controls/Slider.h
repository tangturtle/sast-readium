#pragma once

#include <QSlider>

class Slider : public QSlider {
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = nullptr);
    ~Slider() = default;

    void setMin(double min);
    double min() const;

    void setMax(double max);
    double max() const;

    void setDecimals(int decimals) { Decimals = decimals; }
    int decimals() const { return Decimals; }

    void setVal(double value);
    double val() const;

signals:
    void valueChanged(double value);

private:
    int Decimals = 0;
};
