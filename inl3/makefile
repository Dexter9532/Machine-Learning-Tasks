TARGET := main

SRC_FILES := src/main.cpp \
             src/lin_reg.cpp

COMPILE_FLAGS := -Wall -Werror -std=c++17

INC := inc

default: build run

build:
	@g++ $(SRC_FILES) -o $(TARGET) $(COMPILE_FLAGS) -I$(INC)

run:
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
