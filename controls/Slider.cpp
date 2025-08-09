#include "Slider.h"

Slider::Slider(QWidget *parent) : QSlider(parent) {}

void Slider::setMin(double min) { setMinimum(min * std::pow(10, Decimals)); }

double Slider::min() const { return minimum() / std::pow(10, Decimals); }

void Slider::setMax(double max) { setMaximum(max * std::pow(10, Decimals)); }

double Slider::max() const { return maximum() / std::pow(10, Decimals); }

void Slider::setVal(double value) { setValue(value * std::pow(10, Decimals)); }

double Slider::val() const { return value() / std::pow(10, Decimals); }
