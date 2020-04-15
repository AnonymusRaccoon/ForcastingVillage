/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** xp_component
*/

#ifndef MY_RPG_HEALTH_COMPONENT_H
#define MY_RPG_HEALTH_COMPONENT_H

#include <stdbool.h>
#include "component.h"

struct xp_component
{
    gc_component base;
    int xp;
    bool full;
};

void add_xp(struct xp_component *this, gc_engine *engine, \
unsigned int amount);
void rem_xp(struct xp_component *this, gc_engine *engine, \
unsigned int amount);

extern const struct xp_component xp_component;

#endif //MY_RPG_HEALTH_COMPONENT_H
