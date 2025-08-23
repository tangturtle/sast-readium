# SAST Readium

A Qt6-based PDF reader application with comprehensive build support for multiple environments.

## Features

- Modern Qt6-based PDF viewer
- Cross-platform support (Windows, Linux, macOS)
- Multiple build environments:
  - **vcpkg** for dependency management
  - **MSYS2** for Windows Unix-like development
  - **System packages** for native Linux/macOS builds

## Build Environments

### Windows with vcpkg (Traditional)

```bash
# Configure and build with vcpkg
cmake --preset=Release-Windows
cmake --build --preset=Release-Windows
```

### Windows with MSYS2 (Recommended for Unix-like workflow)

```bash
# Quick start - install dependencies and build
./scripts/build-msys2.sh -d

# Or step by step
./scripts/check-msys2-deps.sh -i  # Install dependencies
./scripts/build-msys2.sh          # Build with system packages
```

For detailed MSYS2 setup and build instructions, see [MSYS2 Build Guide](docs/MSYS2-BUILD.md).

### Linux/macOS

```bash
# Install system dependencies (Ubuntu/Debian example)
sudo apt install cmake ninja-build qt6-base-dev qt6-svg-dev qt6-tools-dev libpoppler-qt6-dev

# Configure and build
cmake --preset=Release-Unix
cmake --build --preset=Release-Unix
```

## Quick Start

### Option 1: MSYS2 (Windows, Unix-like experience)

1. Install [MSYS2](https://www.msys2.org/)
2. Open MSYS2 MINGW64 terminal
3. Clone and build:

   ```bash
   git clone <repository-url>
   cd sast-readium
   ./scripts/build-msys2.sh -d  # Install deps and build
   ```

### Option 2: vcpkg (Windows, traditional)

1. Install [vcpkg](https://vcpkg.io/)
2. Set `VCPKG_ROOT` environment variable
3. Build:

   ```cmd
   cmake --preset=Release-Windows
   cmake --build --preset=Release-Windows
   ```

### Option 3: System packages (Linux/macOS)

1. Install system dependencies
2. Build:

   ```bash
   cmake --preset=Release-Unix
   cmake --build --preset=Release-Unix
   ```

## Build Options

The build system supports flexible dependency management:

- **USE_VCPKG**: Enable/disable vcpkg (auto-detected)
- **FORCE_VCPKG**: Force vcpkg even in MSYS2
- **CMAKE_BUILD_TYPE**: Debug/Release

## Documentation

- [MSYS2 Build Guide](docs/MSYS2-BUILD.md) - Comprehensive MSYS2 setup and build instructions
- [Build Troubleshooting](docs/MSYS2-BUILD.md#troubleshooting) - Common issues and solutions

## Dependencies

- **Qt6** (Core, Gui, Widgets, Svg, LinguistTools)
- **Poppler-Qt6** for PDF rendering
- **CMake** 3.28+ and **Ninja** for building

## License

MIT License - see [LICENSE](LICENSE) for details.
