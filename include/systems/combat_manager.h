/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_manager.h
*/


#ifndef MY_RPG_COMBAT_MANAGER_H
#define MY_RPG_COMBAT_MANAGER_H

#include "system.h"
#include "components/combat_holder.h"
#include "components/dialog_holder.h"

struct combat_manager {
    gc_system base;
    gc_scene *game_scene;
    struct enemy *current_enemy;
};

extern const struct combat_manager combat_manager;

#define ATTACK_TEXT "What attack will you do?"

void combat_start(gc_engine *engine, char *enemy_name);
void show_attacks(struct combat_holder *cmp, struct dialog_holder *dialog, \
gc_scene *scene);

#endif //MY_RPG_COMBAT_MANAGER_H
