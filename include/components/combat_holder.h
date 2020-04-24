/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_holder.h
*/


#ifndef MY_RPG_COMBAT_HOLDER_H
#define MY_RPG_COMBAT_HOLDER_H

#include "component.h"

struct combat_holder
{
    gc_component base;
    char *name;
};

extern const struct combat_holder combat_holder;

#endif //MY_RPG_COMBAT_HOLDER_H
