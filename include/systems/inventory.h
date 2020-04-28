/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** inventory
*/

#ifndef MY_RPG_INVENTORY_H
#define MY_RPG_INVENTORY_H

#include "engine.h"
#include <stdbool.h>

void display_inv_slot(gc_scene *scene, struct renderer *rend, int nb);
bool toggle_inventory(gc_engine *engine);

#endif //MY_RPG_INVENTORY_H
