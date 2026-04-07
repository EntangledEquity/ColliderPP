TARGET_EXEC := game

BUILD_DIR := build
SRC_DIR := src
INC_DIR := include 

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INCS := $(shell find $(INC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INCS))

# Include directories and flags
CPPFLAGS := $(INC_FLAGS) -MMD -MP
# Linker flags for
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system 
# Compiler flags -Wall -Wextra -Werror
CXXFLAGS := -std=c++20 -O3
CXX := g++

# Final executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile cpp → o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

setup:
	sudo apt update
	sudo apt install -y \
		libxrandr-dev \
		libxcursor-dev \
		libxi-dev \
		libudev-dev \
		libfreetype-dev \
		libflac-dev \
		libvorbis-dev \
		libgl1-mesa-dev \
		libegl1-mesa-dev \
		libsfml-dev

-include $(DEPS)