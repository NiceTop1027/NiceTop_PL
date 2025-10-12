CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = nicescript_c
SOURCES = main.c lexer.c value.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c nicescript.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET) ../examples/hello.ns
	./$(TARGET) ../examples/arithmetic.ns

.PHONY: all clean test
