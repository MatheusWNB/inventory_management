TARGET = app

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/**/*.c src/*.c)

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:$(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

fclean:
	rm -f src/*.o $(TARGET)

re: fclean $(TARGET)