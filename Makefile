CC = gcc
CFLAGS = -Wall -pedantic -lncurses

TARGET = ced
SRCS = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -f $(TARGET) && bash

lint:
	cpplint src/*
