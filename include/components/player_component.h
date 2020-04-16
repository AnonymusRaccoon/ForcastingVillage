/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** player_component.h
*/


#ifndef MY_RPG_PLAYER_COMPONENT_H
#define MY_RPG_PLAYER_COMPONENT_H

#include "component.h"

struct player_component
{
    gc_component base;
    int fight_rate;
};

extern const struct player_component player_component;

#endif //MY_RPG_PLAYER_COMPONENT_H
