##
## EPITECH PROJECT, 2019
## MUL_my_runner_2019
## File description:
## Makefile
##

SRC = src/main.c \
	src/game_loader.c \
	src/framerate.c \
	src/main_menu.c \
	src/options.c \
	src/selectors.c \
	src/toolbar.c \
    src/teams/absent.c \
    src/teams/forgot.c \
    src/systems/game_display_system.c \
    src/systems/game_manager_system.c \
    src/systems/teams_system.c \
    src/isometry/map_interactions.c \
    src/isometry/tile_collision_manager.c \
    src/components/map_manager_component.c \
    src/components/game_display.c \
    src/components/game_manager.c \
    src/components/teams_component.c

OBJ = $(SRC:%.c=%.o)

INCLUDE = -I ./include -I lib/gamacon/include -I lib/gamacon/lib/xmlparser/include

CFLAGS = $(INCLUDE) -Wall -Wshadow -Wextra -Wno-unused-parameter

LDFLAGS = -L lib/gamacon -L lib/my -L lib/xmlparser -L lib/quadtree\
-lgamacon -lxmlparser -lquadtree -lmy -lcsfml-system -lcsfml-graphics -lcsfml-audio -lcsfml-window -lm

NAME = my_world

CC = gcc

all: build

build: $(OBJ)
	$(MAKE) -C lib/gamacon
	$(MAKE) -C lib/my
	$(MAKE) -C lib/xmlparser
	$(MAKE) -C lib/quadtree
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(MAKE) -C lib/gamacon clean
	$(MAKE) -C lib/my clean
	$(MAKE) -C lib/xmlparser clean
	$(MAKE) -C lib/quadtree clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

ffclean: fclean
	$(MAKE) -C lib/my fclean
	$(MAKE) -C lib/gamacon fclean
	$(MAKE) -C lib/xmlparser fclean
	$(MAKE) -C lib/quadtree fclean

re: fclean all

dbg: CFLAGS += -g
dbg: clean $(OBJ)
	$(MAKE) -C lib/gamacon dbg
	$(MAKE) -C lib/my
	$(MAKE) -C lib/xmlparser dbg
	$(MAKE) -C lib/quadtree dbg
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

.PHONY: all build clean fclean ffclean