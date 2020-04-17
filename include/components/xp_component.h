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

void xp_add(struct xp_component *this, gc_engine *engine, \
unsigned int amount);
void xp_rem(struct xp_component *this, gc_engine *engine, \
unsigned int amount);

extern const struct xp_component xp_component;

#endif //MY_RPG_HEALTH_COMPONENT_H
