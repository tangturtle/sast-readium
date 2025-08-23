cmake_minimum_required(VERSION 3.28)
project(sast-readium LANGUAGES CXX VERSION 0.1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# MSYS2 and vcpkg configuration
option(USE_VCPKG "Use vcpkg for dependency management" OFF)
option(FORCE_VCPKG "Force vcpkg usage even in MSYS2" OFF)

# Detect MSYS2 environment
if(WIN32 AND DEFINED ENV{MSYSTEM})
    set(MSYS2_DETECTED TRUE)
    message(STATUS "MSYS2 environment detected: $ENV{MSYSTEM}")
else()
    set(MSYS2_DETECTED FALSE)
endif()

# Determine whether to use vcpkg
if(FORCE_VCPKG)
    set(USE_VCPKG_INTERNAL TRUE)
    message(STATUS "vcpkg usage forced via FORCE_VCPKG option")
elseif(MSYS2_DETECTED AND NOT USE_VCPKG)
    set(USE_VCPKG_INTERNAL FALSE)
    message(STATUS "MSYS2 detected - using system packages instead of vcpkg")
else()
    set(USE_VCPKG_INTERNAL ${USE_VCPKG})
    if(USE_VCPKG_INTERNAL)
        message(STATUS "Using vcpkg for dependency management")
    else()
        message(STATUS "Using system packages for dependency management")
    endif()
endif()

# Configure dependency finding based on build environment
if(USE_VCPKG_INTERNAL)
    # vcpkg mode - use CONFIG mode for all packages
    find_package(
        Qt6
        COMPONENTS Core Gui Widgets Svg LinguistTools
        CONFIG
        REQUIRED
    )
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(POPPLER_QT6 REQUIRED IMPORTED_TARGET poppler-qt6)
else()
    # System packages mode (MSYS2 or other system package managers)
    if(MSYS2_DETECTED)
        # MSYS2-specific package finding
        message(STATUS "Configuring for MSYS2 environment")

        # Set Qt6 installation path for MSYS2
        if(DEFINED ENV{MSYSTEM_PREFIX})
            list(APPEND CMAKE_PREFIX_PATH "$ENV{MSYSTEM_PREFIX}")
            message(STATUS "Added MSYSTEM_PREFIX to CMAKE_PREFIX_PATH: $ENV{MSYSTEM_PREFIX}")
        endif()

        # Find Qt6 using system installation
        find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg LinguistTools)

        # Find poppler-qt6 using pkg-config
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(POPPLER_QT6 REQUIRED IMPORTED_TARGET poppler-qt6)

        # MSYS2 specific configurations
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            # Strip debug symbols in release builds for smaller binaries
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
        endif()
    else()
        # Generic system package finding
        find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg LinguistTools)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(POPPLER_QT6 REQUIRED IMPORTED_TARGET poppler-qt6)
    endif()
endif()

qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES zh)

add_subdirectory(controls)
add_subdirectory(app)

# MSYS2-specific post-build configurations
if(MSYS2_DETECTED)
    # Print build information
    message(STATUS "=== MSYS2 Build Configuration ===")
    message(STATUS "MSYSTEM: $ENV{MSYSTEM}")
    message(STATUS "MSYSTEM_PREFIX: $ENV{MSYSTEM_PREFIX}")
    message(STATUS "Using vcpkg: ${USE_VCPKG_INTERNAL}")
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "================================")

    # Set RPATH for MSYS2 libraries
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    endif()
endif()
