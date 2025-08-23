# Makefile for sast-readium project
# Provides convenient targets for common development tasks

.PHONY: help configure build clean clangd-config clangd-list clangd-auto test

# Default target
help:
	@echo "Available targets:"
	@echo "  configure     - Configure the project (Debug build)"
	@echo "  configure-release - Configure the project (Release build)"
	@echo "  build         - Build the project"
	@echo "  clean         - Clean build artifacts"
	@echo "  clangd-config - Update clangd configuration (auto-detect)"
	@echo "  clangd-list   - List available build configurations"
	@echo "  clangd-auto   - Auto-detect and set best clangd configuration"
	@echo "  test          - Run tests (if available)"
	@echo "  help          - Show this help message"

# Configure project (Debug)
configure:
	cmake --preset Debug

# Configure project (Release)
configure-release:
	cmake --preset Release

# Build project
build:
	cmake --build build/Debug

# Build project (Release)
build-release:
	cmake --build build/Release

# Clean build artifacts
clean:
	rm -rf build/Debug build/Release

# Update clangd configuration (auto-detect)
clangd-config: clangd-auto

# List available clangd configurations
clangd-list:
	@if [ -f scripts/update-clangd-config.sh ]; then \
		chmod +x scripts/update-clangd-config.sh; \
		./scripts/update-clangd-config.sh --list; \
	else \
		echo "Error: clangd configuration script not found"; \
	fi

# Auto-detect and set best clangd configuration
clangd-auto:
	@if [ -f scripts/update-clangd-config.sh ]; then \
		chmod +x scripts/update-clangd-config.sh; \
		./scripts/update-clangd-config.sh --auto; \
	else \
		echo "Error: clangd configuration script not found"; \
	fi

# Set specific clangd configuration
clangd-debug:
	@if [ -f scripts/update-clangd-config.sh ]; then \
		chmod +x scripts/update-clangd-config.sh; \
		./scripts/update-clangd-config.sh --build-dir "build/Debug"; \
	else \
		echo "Error: clangd configuration script not found"; \
	fi

clangd-release:
	@if [ -f scripts/update-clangd-config.sh ]; then \
		chmod +x scripts/update-clangd-config.sh; \
		./scripts/update-clangd-config.sh --build-dir "build/Release"; \
	else \
		echo "Error: clangd configuration script not found"; \
	fi

# Run tests (placeholder)
test:
	@echo "Tests not yet implemented"

# Development workflow
dev: configure clangd-auto
	@echo "Development environment ready!"
	@echo "You can now:"
	@echo "  - Run 'make build' to build the project"
	@echo "  - Use your IDE with clangd for code completion"
	@echo "  - Run 'make clangd-list' to see available configurations"
