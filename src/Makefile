CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = test
SRC = test.c

all: build

build: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) 

run: build
	./$(TARGET) test1.txt testout.txt

clean:
	rm -f $(TARGET) testout.txt

.PHONY: all build run clean
