CC = gcc
CFLAGS = -lncurses

TARGET = ced
SRCS = main.c editor.c cedfile.c cedline.c titlebar.c filehandler.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -f $(TARGET)
