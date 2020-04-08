LIB_PATH=/home/yaoliu/src_code/protobuf-java-3.7.0.jar

SRC_DIR := src
SRCS = $(shell find $(SRC_DIR) -name "*.java")

.PHONY: clean

all: clean
	mkdir bin
	javac -classpath $(LIB_PATH) -d bin/ $(SRCS) 

clean:
	rm -rf bin/