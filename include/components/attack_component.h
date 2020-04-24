/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** attack_component.hMdr
*/


#ifndef MY_RPG_ATTACK_COMPONENT_H
#define MY_RPG_ATTACK_COMPONENT_H

#include "component.h"

typedef void (*attack)(gc_engine *engine, gc_entity *from, gc_entity *enemy);

typedef struct attack_holder {
    char *name;
    attack run;
} attack_holder;

struct attack_component {
    gc_component base;
    attack_holder *attacks;
};

extern const struct attack_component attack_component;

#endif //MY_RPG_ATTACK_COMPONENT_H
