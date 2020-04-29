##
## EPITECH PROJECT, 2019
## MUL_my_runner_2019
## File description:
## Makefile
##

SRC = 	src/main.c \
	src/game_loader.c \
	src/framerate.c \
	src/main_menu.c \
	src/options.c \
	src/systems/game_manager_system.c \
	src/components/game_manager.c \
	src/components/game_display.c \
	src/components/map_movement.c \
	src/components/controllable_component.c \
	src/components/controllers/keyboard_controller.c \
	src/components/dialog_holder.c \
	src/components/dialog_methods.c \
	src/systems/map_movement_system.c \
	src/systems/game_display_system.c \
	src/systems/dialog_manager.c \
	src/systems/controllers/keyboard_controller_system.c \
	src/map_editor/map_interactions.c \
	src/map_editor/brush_component.c \
	src/map_editor/selectors.c \
	src/map_editor/toolbar.c \
	src/components/health_component.c \
	src/components/health_methods.c \
	src/components/xp_component.c \
	src/components/xp_methods.c \
	src/dialog_input.c \
	src/systems/dialog_methods.c \
	src/systems/combat_manager.c \
	src/components/player_component.c \
	src/components/attack_component.c \
	src/systems/combat_methods.c \
	src/components/combat_holder.c \
	src/enemy_dataloader.c \
	src/combat/attacks.c \
	src/player_utilities.c \
	src/systems/inventory.c

OBJ = $(SRC:%.c=%.o)

INCLUDE = -I ./include -I lib/gamacon/include -I lib/gamacon/lib/xmlparser/include

CFLAGS = $(INCLUDE) -Wall -Wshadow -Wextra -Wno-unused-parameter

LDFLAGS = -L lib/gamacon -L lib/my -L lib/xmlparser -L lib/quadtree \
	-lgamacon -lxmlparser -lquadtree -lmy -lcsfml-system -lcsfml-graphics -lcsfml-audio -lcsfml-window -lm

NAME = my_rpg

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

.PHONY: all build clean fclean ffclean dbg re
