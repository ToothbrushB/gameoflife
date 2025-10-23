CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/main.c src/board.c src/cell.c
OBJ = $(SRC:.c=.o)
TARGET = gameoflife

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)