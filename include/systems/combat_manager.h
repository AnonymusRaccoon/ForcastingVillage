/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_manager.h
*/


#ifndef MY_RPG_COMBAT_MANAGER_H
#define MY_RPG_COMBAT_MANAGER_H

#include <components/attack_component.h>
#include "system.h"
#include "components/combat_holder.h"
#include "components/dialog_holder.h"

enum combat_state
{
    ATTACK,
    DEFEND,
    ATTACKING,
    DEFENDING,
    IDLE
};

struct combat_manager {
    gc_system base;
    gc_scene *game_scene;
    struct enemy *current_enemy;
    struct attack_holder *next_enemy_attack;
    enum combat_state state;
};

extern const struct combat_manager combat_manager;

#define ATTACK_TEXT "What attack will you do?"

void combat_start(gc_engine *engine, char *enemy_name);
void show_attacks(struct combat_manager *this, struct dialog_holder *dialog, \
gc_scene *scene, gc_engine *engine);
void defend(struct combat_manager *this, struct dialog_holder *dialog, \
gc_scene *scene, gc_engine *engine);

#endif //MY_RPG_COMBAT_MANAGER_H
