-- xmake.lua for SAST Readium
-- A Qt6-based PDF reader application with comprehensive build support

-- Set minimum xmake version
set_xmakever("2.8.0")

-- Project metadata
set_project("sast-readium")
set_version("0.1.0.0")
set_description("SAST Readium - A Qt6-based PDF reader application")

-- Language and standards
set_languages("cxx20")
set_warnings("all")

-- Build modes
add_rules("mode.debug", "mode.release")

-- Force MinGW toolchain to avoid Qt detection issues
set_toolchains("mingw")

-- Package requirements (only non-Qt packages)
add_requires("pkgconfig::poppler-qt6")

-- Build options
option("enable_clangd")
    set_default(true)
    set_description("Enable clangd configuration generation")
    set_showmenu(true)
option_end()

option("enable_tests")
    set_default(false)
    set_description("Enable building tests")
    set_showmenu(true)
option_end()

option("enable_examples")
    set_default(false)
    set_description("Enable building examples")
    set_showmenu(true)
option_end()

-- Detect MSYS2 environment
function is_msys2()
    return is_plat("windows") and os.getenv("MSYSTEM")
end

-- Main application target
target("sast-readium")
    set_kind("binary")

    -- Add Qt rules for MOC processing
    add_rules("qt.moc")

    -- Explicitly add headers that need MOC processing
    add_files("app/MainWindow.h")
    add_files("app/model/DocumentModel.h")
    add_files("app/model/PageModel.h")
    add_files("app/model/RenderModel.h")
    add_files("app/model/PDFOutlineModel.h")
    add_files("app/controller/DocumentController.h")
    add_files("app/controller/PageController.h")
    add_files("app/managers/StyleManager.h")
    add_files("app/managers/RecentFilesManager.h")
    add_files("app/ui/viewer/PDFViewer.h")
    add_files("app/ui/viewer/PDFOutlineWidget.h")
    add_files("app/ui/widgets/DocumentTabWidget.h")
    add_files("app/ui/widgets/SearchWidget.h")
    add_files("app/ui/widgets/BookmarkWidget.h")
    add_files("app/ui/widgets/AnnotationToolbar.h")
    add_files("app/ui/thumbnail/ThumbnailModel.h")
    add_files("app/ui/thumbnail/ThumbnailDelegate.h")
    add_files("app/ui/thumbnail/ThumbnailListView.h")
    add_files("app/ui/thumbnail/ThumbnailGenerator.h")
    add_files("app/model/AsyncDocumentLoader.h")
    add_files("app/ui/dialogs/DocumentMetadataDialog.h")
    add_files("app/ui/dialogs/DocumentComparison.h")
    add_files("app/ui/core/ViewWidget.h")
    add_files("app/ui/core/StatusBar.h")
    add_files("app/ui/core/SideBar.h")
    add_files("app/ui/core/MenuBar.h")
    add_files("app/ui/core/ToolBar.h")
    add_files("app/factory/WidgetFactory.h")
    add_files("app/model/SearchModel.h")
    add_files("app/model/BookmarkModel.h")
    add_files("app/model/AnnotationModel.h")
    add_files("app/ui/viewer/PDFPrerenderer.h")
    add_files("app/ui/viewer/PDFAnimations.h")
    add_files("app/ui/viewer/PDFViewerEnhancements.h")
    add_files("app/command/Commands.h")
    add_files("app/ui/managers/PerformanceMonitor.h")
    add_files("app/ui/managers/AccessibilityManager.h")
    add_files("app/cache/PDFCacheManager.h")
    add_files("app/plugin/PluginManager.h")
    add_files("app/delegate/PageNavigationDelegate.h")
    add_files("app/utils/DocumentAnalyzer.h")
    add_files("app/ui/thumbnail/ThumbnailWidget.h")
    add_files("app/ui/thumbnail/ThumbnailContextMenu.h")
    add_files("app/view/Views.h")

    -- Set output directory
    set_targetdir("$(builddir)")
    
    -- Manual Qt configuration
    if is_plat("windows") then
        -- Always use MSYS2 Qt paths since we're in MSYS2 environment
        local qt_base = "D:/msys64/mingw64"

        -- Include directories (order matters!)
        add_includedirs(qt_base .. "/include/qt6")
        add_includedirs(qt_base .. "/include/qt6/QtCore")
        add_includedirs(qt_base .. "/include/qt6/QtGui")
        add_includedirs(qt_base .. "/include/qt6/QtWidgets")
        add_includedirs(qt_base .. "/include/qt6/QtSvg")
        add_includedirs(qt_base .. "/include/qt6/QtConcurrent")

        -- Library directories and links
        add_linkdirs(qt_base .. "/lib")
        -- Use MinGW library names (libQt6Core.dll.a, etc.)
        add_links("Qt6Core", "Qt6Gui", "Qt6Widgets", "Qt6Svg", "Qt6Concurrent")

        -- Qt defines
        add_defines("QT_CORE_LIB", "QT_GUI_LIB", "QT_WIDGETS_LIB", "QT_SVG_LIB")
        add_defines("QT_NO_DEBUG")

        print("Using MSYS2 Qt with MinGW compiler")
    end
    
    -- Add poppler-qt6 dependency
    add_packages("pkgconfig::poppler-qt6")
    
    -- Generate config.h from template
    before_build(function (target)
        local config_content = [[#pragma once

#define PROJECT_NAME "sast-readium"
#define APP_NAME "SAST Readium - A Qt6-based PDF reader application"
#define PROJECT_VER "0.1.0.0"
#define PROJECT_VER_MAJOR "0"
#define PROJECT_VER_MINOR "1"
#define PROJECT_VER_PATCH "0"
]]
        io.writefile("app/config.h", config_content)
        print("Generated config.h")
    end)

    -- Include directories
    add_includedirs(".", "app", "$(builddir)")
    add_includedirs("app/ui", "app/ui/core", "app/ui/viewer", "app/ui/widgets")
    add_includedirs("app/ui/dialogs", "app/ui/thumbnail", "app/ui/managers")
    add_includedirs("app/managers", "app/model", "app/controller", "app/delegate")
    add_includedirs("app/view", "app/cache", "app/utils", "app/plugin")
    add_includedirs("app/factory", "app/command", "app/performance")
    
    -- Compiler settings
    set_languages("cxx20")
    add_cxxflags("-std=c++20")
    set_warnings("all")
    
    -- Build mode specific settings
    if is_mode("release") then
        set_optimize("fastest")
        add_defines("NDEBUG")
        set_symbols("hidden")
    else
        set_optimize("none")
        set_symbols("debug")
        add_defines("DEBUG", "_DEBUG")
    end
    
    -- Platform-specific configurations
    if is_plat("windows") then
        add_defines("WIN32", "_WINDOWS", "UNICODE", "_UNICODE")
        if is_mode("release") then
            set_kind("binary")
        end
        
        -- Windows RC file
        add_files("app/app.rc")
    end

    -- Translation files (Qt rules disabled to avoid assertion errors)
    -- add_files("app/i18n/app_en.ts")
    -- add_files("app/i18n/app_zh.ts")
    -- add_rules("qt.ts")
    -- set_values("qt.ts.lupdate", "app/i18n/app_en.ts", "app/i18n/app_zh.ts")

    -- Main source files
    add_files("app/main.cpp")
    add_files("app/MainWindow.cpp")

    -- Core UI components
    add_files("app/ui/core/ViewWidget.cpp")
    add_files("app/ui/core/StatusBar.cpp")
    add_files("app/ui/core/SideBar.cpp")
    add_files("app/ui/core/MenuBar.cpp")
    add_files("app/ui/core/ToolBar.cpp")

    -- Models (essential for linking)
    add_files("app/model/DocumentModel.cpp")
    add_files("app/model/PageModel.cpp")
    add_files("app/model/RenderModel.cpp")
    add_files("app/model/PDFOutlineModel.cpp")
    add_files("app/model/AsyncDocumentLoader.cpp")
    add_files("app/model/SearchModel.cpp")
    add_files("app/model/BookmarkModel.cpp")
    add_files("app/model/AnnotationModel.cpp")

    -- Controllers
    add_files("app/controller/DocumentController.cpp")
    add_files("app/controller/PageController.cpp")

    -- Managers
    add_files("app/managers/StyleManager.cpp")
    add_files("app/managers/RecentFilesManager.cpp")

    -- UI Manager components
    add_files("app/ui/managers/PerformanceMonitor.cpp")
    add_files("app/ui/managers/AccessibilityManager.cpp")

    -- Cache management
    add_files("app/cache/PDFCacheManager.cpp")

    -- Utilities
    add_files("app/utils/PDFUtilities.cpp")
    add_files("app/utils/DocumentAnalyzer.cpp")

    -- Plugin system
    add_files("app/plugin/PluginManager.cpp")

    -- Factory
    add_files("app/factory/WidgetFactory.cpp")

    -- Command system
    add_files("app/command/Commands.cpp")

    -- Viewer components
    add_files("app/ui/viewer/PDFViewer.cpp")
    add_files("app/ui/viewer/PDFOutlineWidget.cpp")
    add_files("app/ui/viewer/PDFViewerEnhancements.cpp")
    add_files("app/ui/viewer/PDFAnimations.cpp")
    add_files("app/ui/viewer/PDFPrerenderer.cpp")

    -- Widget components
    add_files("app/ui/widgets/DocumentTabWidget.cpp")
    add_files("app/ui/widgets/SearchWidget.cpp")
    add_files("app/ui/widgets/BookmarkWidget.cpp")
    add_files("app/ui/widgets/AnnotationToolbar.cpp")

    -- Dialog components
    add_files("app/ui/dialogs/DocumentComparison.cpp")
    add_files("app/ui/dialogs/DocumentMetadataDialog.cpp")

    -- Thumbnail system
    add_files("app/ui/thumbnail/ThumbnailWidget.cpp")
    add_files("app/ui/thumbnail/ThumbnailModel.cpp")
    add_files("app/ui/thumbnail/ThumbnailDelegate.cpp")
    add_files("app/ui/thumbnail/ThumbnailGenerator.cpp")
    add_files("app/ui/thumbnail/ThumbnailListView.cpp")
    add_files("app/ui/thumbnail/ThumbnailContextMenu.cpp")

    -- Delegates
    add_files("app/delegate/PageNavigationDelegate.cpp")

    -- Views
    add_files("app/view/Views.cpp")

    -- Add all header files for proper organization
    add_headerfiles("app/*.h")
    add_headerfiles("app/ui/core/*.h")
    add_headerfiles("app/ui/viewer/*.h")
    add_headerfiles("app/ui/widgets/*.h")
    add_headerfiles("app/ui/dialogs/*.h")
    add_headerfiles("app/ui/thumbnail/*.h")
    add_headerfiles("app/ui/managers/*.h")
    add_headerfiles("app/managers/*.h")
    add_headerfiles("app/model/*.h")
    add_headerfiles("app/controller/*.h")
    add_headerfiles("app/delegate/*.h")
    add_headerfiles("app/view/*.h")
    add_headerfiles("app/cache/*.h")
    add_headerfiles("app/utils/*.h")
    add_headerfiles("app/plugin/*.h")
    add_headerfiles("app/factory/*.h")
    add_headerfiles("app/command/*.h")
    add_headerfiles("app/performance/*.h")

    -- Custom rules for asset copying
    after_build(function (target)
        -- Copy assets/styles directory to build output
        local targetdir = target:targetdir()
        os.cp("assets/styles", path.join(targetdir, "styles"))
        print("Copied assets/styles to %s", path.join(targetdir, "styles"))
    end)

target_end()

-- Optional: Test target
if has_config("enable_tests") then
    target("sast-readium-tests")
        set_kind("binary")
        set_default(false)
        add_deps("sast-readium")
        add_files("tests/*.cpp")
        add_packages("pkgconfig::poppler-qt6")
    target_end()
end

-- Optional: Example target
if has_config("enable_examples") then
    target("sast-readium-example")
        set_kind("binary")
        set_default(false)
        add_files("app/example/*.cpp")
        add_packages("pkgconfig::poppler-qt6")
    target_end()
end

-- Print build configuration
after_build(function (target)
    print("=== Build Configuration Summary ===")
    print("Build mode: %s", get_config("mode"))
    print("C++ Standard: cxx20")
    print("Platform: %s", get_config("plat"))
    print("Architecture: %s", get_config("arch"))
    if is_msys2() then
        print("MSYS2 environment detected")
        print("MSYSTEM: %s", os.getenv("MSYSTEM"))
    end
    print("Qt: Manual configuration (auto-detection disabled)")
    print("=====================================")
end)
