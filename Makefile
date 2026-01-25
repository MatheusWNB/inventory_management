TARGET = app

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O2

SRC = $(wildcard src/**/*.c src/*.c)

OBJ = $(SRC:.c=.o)

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: debug
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

fclean:
	rm -f src/*.o $(TARGET)

re: fclean $(TARGET)