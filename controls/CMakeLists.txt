add_library(controls)
target_sources(
    controls
    PRIVATE
    Slider.cpp
)
target_link_libraries(
    controls
    PRIVATE
    Qt::Core Qt::Gui Qt::Widgets Qt::Svg
)