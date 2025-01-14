CC = gcc
CFLAGS = -Wall -Wextra -I../include
BUILD_DIR = ../build
SOURCES = menu.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BUILD_DIR)/coffee_shop

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) -lncurses

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)