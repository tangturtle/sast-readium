# Cross-compilation toolchain for Linux ARM64 (aarch64)
# This toolchain file enables cross-compilation from x86_64 Linux to ARM64 Linux

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Cross-compilation tools
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc)

# Cross-compilation tool prefixes
set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set the architecture for pkg-config
set(ENV{PKG_CONFIG_PATH} "/usr/lib/aarch64-linux-gnu/pkgconfig")
set(ENV{PKG_CONFIG_LIBDIR} "/usr/lib/aarch64-linux-gnu/pkgconfig:/usr/share/pkgconfig")

# Qt6 specific settings for cross-compilation
set(QT_HOST_PATH "/usr" CACHE PATH "Path to host Qt installation")
set(CMAKE_PREFIX_PATH "/usr/lib/aarch64-linux-gnu/cmake" CACHE PATH "Path to ARM64 CMake modules")

# Compiler flags for ARM64
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link,/usr/lib/aarch64-linux-gnu")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link,/usr/lib/aarch64-linux-gnu")

# Set target architecture for vcpkg if used
set(VCPKG_TARGET_TRIPLET "arm64-linux" CACHE STRING "")
