/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#ifndef MY_RPG_PLAYER_UTILITIES_H
#define MY_RPG_PLAYER_UTILITIES_H

#include "entity.h"

void set_combat_player(gc_engine *engine, gc_entity *main_player, \
gc_entity *combat_player);

bool get_player_and_enemy(gc_scene *sce, gc_entity **player, \
gc_entity **enemy);
void combat_create_enemy(struct combat_manager *this, gc_engine *engine, \
char *enemy_name);

#endif //MY_RPG_PLAYER_UTILITIES_H
