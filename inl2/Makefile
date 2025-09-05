TARGET := main

SOURCE_FILES := src/main.cpp \
                src/car.cpp

COMPILER_FLAGS := -Wall -Werror

INCLUDE_DIRS := -Iinc/

default: build run

build:
	@g++ $(SOURCE_FILES) -o $(TARGET) $(INCLUDE_DIRS) $(COMPILER_FLAGS)

run:
	@./$(TARGET)

clean:l
	@rm -f $(TARGET)
