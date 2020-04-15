/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct controllable_component
{
    gc_component base;
    int movement_x;
    int movement_y;
    float move_callback;
    bool can_move;
};

void controllable_set_can_move(gc_scene *scene, bool value);

extern const struct controllable_component controllable_component;