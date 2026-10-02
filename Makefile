CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -IInclude
BUILD_DIR := build
SRC_DIR := Source

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

ifeq ($(OS),Windows_NT)
    TARGET := VehicleManagSys.exe
    CLEAN_CMD := if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR) & if exist $(TARGET) del /f /q $(TARGET) & if exist VehicleManagSys del /f /q VehicleManagSys
    MKDIR_CMD := if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
    TARGET := VehicleManagSys
    CLEAN_CMD := rm -rf $(BUILD_DIR) $(TARGET) $(TARGET).exe
    MKDIR_CMD := mkdir -p $(BUILD_DIR)
endif

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo [LINK] Linking $@...
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo [SUCCESS] Build complete: $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo [CXX] $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@$(MKDIR_CMD)

run: all
	@echo [RUN] Launching $(TARGET)...
	./$(TARGET)

clean:
	@echo [CLEAN] Removing build files...
	@$(CLEAN_CMD)
