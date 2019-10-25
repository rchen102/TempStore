INCLUDE_DIR := include
SRC_DIR := src
OBJ_DIR := obj
TARGET := predictors

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HDRS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CFLAGS=-g -Wall -std=c++14

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	g++ $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) short_trace1.txt output.txt

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
