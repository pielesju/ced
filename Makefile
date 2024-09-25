CC = gcc
CFLAGS = -lncurses

TARGET = ced
SRCS = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -f $(TARGET)
