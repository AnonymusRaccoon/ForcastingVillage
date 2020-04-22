/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** attack_component.h
*/


#ifndef MY_RPG_ATTACK_COMPONENT_H
#define MY_RPG_ATTACK_COMPONENT_H

#include "component.h"

typedef void (*attack)(gc_entity *from, gc_entity *enemy);

struct attack_component {
    gc_component base;
    gc_data *attacks;
};

extern const struct attack_component attack_component;

#endif //MY_RPG_ATTACK_COMPONENT_H
