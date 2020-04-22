/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_holder.h
*/


#ifndef MY_RPG_COMBAT_HOLDER_H
#define MY_RPG_COMBAT_HOLDER_H

#include "component.h"

enum combat_state
{
    ATTACK,
    ATTACKING,
    DEFENDING,
    IDLE
};

struct combat_holder
{
    gc_component base;
    enum combat_state state;
    char *name;
};

extern const struct combat_holder combat_holder;

#endif //MY_RPG_COMBAT_HOLDER_H
