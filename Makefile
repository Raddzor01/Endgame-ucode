CC = clang
CFLAGS = -std=c11 -Werror -Wall -Wextra -Wpedantic -g -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lrt
FUNCTIONS = src/*.c
FOLDER = obj
A_FILE = minilibmx.a
NAME = endgame
OBJECTS = obj/*.o

all: $(NAME) clean
$(NAME):
	@$(CC) $(CFLAGS) $(FUNCTIONS) -o $@ -I inc
clean:
	rm -rf src/*.h
uninstall: clean
	rm -rf $(NAME)
reinstall: uninstall all
