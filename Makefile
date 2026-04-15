.PHONY: all clean rebuild

# Path to WASI SDK
WASI_SDK_PATH ?= wasi-sdk-20.0+threads

CC = $(WASI_SDK_PATH)/bin/clang
SYSROOT = $(WASI_SDK_PATH)/share/wasi-sysroot

CFLAGS = --sysroot=$(SYSROOT) \
         --target=wasm32-wasi-threads \
         -pthread

LDFLAGS = -Wl,--import-memory \
          -Wl,--export-memory \
          -Wl,--max-memory=67108864

SRC_DIR = source

# Targets
all: main.wasm cv.wasm

rebuild: clean all

main.wasm:
	$(CC) $(CFLAGS) $(LDFLAGS) \
	$(SRC_DIR)/mainDemo.c \
	$(SRC_DIR)/spinlock.c \
	$(SRC_DIR)/yieldSpinlock.c \
	$(SRC_DIR)/blockMutex.c \
	-o $@

cv.wasm:
	$(CC) $(CFLAGS) $(LDFLAGS) \
	$(SRC_DIR)/cvDemo.c \
	$(SRC_DIR)/conditionVars.c \
	$(SRC_DIR)/blockMutex.c \
	$(SRC_DIR)/semaphore.c \
	-o $@

clean:
	rm -f main.wasm cv.wasm