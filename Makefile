CC = gcc
CFLAGS = -Wall -Wextra

TARGET = calcFrequency
SRC = main.c
OBJ = $(SRC:.c=.o)

INPUT_FILE = text1.txt
OUTPUT_FILE = text2.txt

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	@./$(TARGET) $(INPUT_FILE) $(OUTPUT_FILE)