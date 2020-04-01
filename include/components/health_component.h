/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** health_component
*/

#ifndef MY_RPG_HEALTH_COMPONENT_H
#define MY_RPG_HEALTH_COMPONENT_H

#include <stdbool.h>
#include "component.h"

struct health_component
{
    gc_component base;
    int health;
    bool dead;
};

void add_health(struct health_component *this, gc_engine *engine, \
unsigned int amount);
void rem_health(struct health_component *this, gc_engine *engine, \
unsigned int amount);

extern const struct health_component health_component;

#endif //MY_RPG_HEALTH_COMPONENT_H
