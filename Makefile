CC = gcc
CFLAGS = -Wall -Wextra -I./include
BUILD_DIR = build

SOURCES = src/menu.c
OBJECTS = $(BUILD_DIR)/menu.o
EXECUTABLE = $(BUILD_DIR)/coffee_shop

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) -lncurses

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
