CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -O0 -Iinclude
OBJS = src/main.o src/list.o src/io.o
TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc $^ -o $@

src/%.o: src/%.c include/list.h include/io.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
