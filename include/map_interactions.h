/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_interactions
*/


#ifndef MY3D_MAP_INTERACTIONS_H
#define MY3D_MAP_INTERACTIONS_H

#include "engine.h"
#include "components/vertex_component.h"
#include "keybindings.h"

enum modes_on_tile {
    VERTEX_0 = 2,
    VERTEX_1 = 4,
    VERTEX_2 = 8,
    VERTEX_3 = 16,
    ALL_VERTICES = 30,
    INVERT_ADD_VALUE = 1
};

bool map_onclick(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);

#endif //MY3D_MAP_INTERACTIONS_H
