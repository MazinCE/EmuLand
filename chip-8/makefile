OBJS = src/main.c src/chip8.c src/display.c src/keypad.c 
CC = gcc
COMPILER_FLAGS = -Wall -g
LINKER_FLAGS = -lSDL2
OBJ_NAME = chip-8

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm *.o chip-8