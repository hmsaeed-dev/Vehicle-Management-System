CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -IInclude
TARGET := VehicleManagSys
BUILD_DIR := build
SRC_DIR := Source

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "[LINK] Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[SUCCESS] Build complete: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "[CXX] $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	@echo "[RUN] Launching $(TARGET)..."
	./$(TARGET)

clean:
	@echo "[CLEAN] Removing build files..."
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET).exe
