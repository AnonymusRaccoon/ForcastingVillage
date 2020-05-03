/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** particule_system
*/

#ifndef MY_RPG_PARTICULE_SYSTEM_H
#define MY_RPG_PARTICULE_SYSTEM_H

#include "engine.h"
#include "components/particule_component.h"

void particule_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dt);
void create_particule(struct particule *particule, int lifetime, \
void *texture, gc_vector2 pos);
void create_particule(struct particule *particule, int lifetime, \
void *texture, gc_vector2 pos);
void particule_draw(gc_engine *engine, gc_entity *entity, float dt);

extern const struct gc_system particule_system;

#endif //MY_RPG_PARTICULE_SYSTEM_H
