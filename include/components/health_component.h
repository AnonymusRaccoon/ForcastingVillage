/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** health_component
*/

#ifndef MY_RPG_HEALTH_COMPONENT_H
#define MY_RPG_HEALTH_COMPONENT_H

#include "component.h"

struct health_component
{
    gc_component base;
    unsigned int health;
};

extern const struct health_component health_component;

#endif //MY_RPG_HEALTH_COMPONENT_H
