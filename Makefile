CC = gcc
CFLAGS = -Wall -Wextra

TARGET = calcFrequency
SRC = main.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET) $(ARGS)