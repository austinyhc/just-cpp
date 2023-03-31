.PHONY: all build cmake

SHELL := /bin/bash
PROJECT_NAME := leetlib
BUILD_DIR ?= build
BUILD_TYPE ?= Debug

# TODO: Figure out the syntax
PLATFORM = $(if $(OS),$(OS),$(shell uname -s))
BUILD_SYSTEM = Unix Makefiles

all: build

build: cmake
	$(MAKE) -C $(BUILD_DIR) --no-print-directory

cmake: $(BUILD_DIR)/Makefile

$(BUILD_DIR)/Makefile: CMakeLists.txt
	cmake \
		-G "$(BUILD_SYSTEM)" \
		-B$(BUILD_DIR) \
		-DPROJECT_NAME=$(PROJECT_NAME) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1

clean:
	rm -rf $(BUILD_DIR)
