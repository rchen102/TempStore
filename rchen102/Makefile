INCLUDE_DIR := include
SRC_DIR := src
OBJ_DIR := obj
TARGET := cache-sim

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HDRS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CFLAGS = -g -Wall -std=c++14

INPUT = files/traces/trace1.txt
OUTPUT = files/output/output.txt
CORRECT = files/correct_outputs/trace1_output.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	g++ $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) $(INPUT) $(OUTPUT)


.PHONY: clean diff
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(OUTPUT)

diff:
	diff $(OUTPUT) $(CORRECT)
