/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_manager.h
*/


#ifndef MY_RPG_COMBAT_MANAGER_H
#define MY_RPG_COMBAT_MANAGER_H

#include "system.h"

struct combat_manager {
    gc_system base;
    gc_scene *game_scene;
    struct enemy *current_enemy;
};

extern const struct combat_manager combat_manager;

#endif //MY_RPG_COMBAT_MANAGER_H
