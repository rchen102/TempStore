INCLUDE_DIR := include
SRC_DIR := src
OBJ_DIR := obj
TARGET := cache-sim

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HDRS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CFLAGS = -g -Wall -std=c++14

TRACE = trace1
INPUT = files/traces/$(TRACE).txt
OUTPUT = files/output.txt
CORRECT = files/correct_outputs/$(TRACE)_output.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	g++ $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) $(INPUT) $(OUTPUT)

memcheck: all
	valgrind --track-origins=yes --leak-check=full ./$(TARGET) files/test/input.txt files/test/output.txt


.PHONY: clean diff
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(OUTPUT)

diff: run
	diff $(OUTPUT) $(CORRECT)
