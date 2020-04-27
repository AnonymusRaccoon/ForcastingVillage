/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** fireball.c
*/

#include <components/health_component.h>
#include "engine.h"

void uppercut(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    struct health_component *enemy_health = GETCMP(enemy, health_component);

    rem_health(enemy_health, engine, 10);
}

void water_jet(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    printf("water_grenade\n");
}

void fireball(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    printf("FIREBALL\n");
}

void shield(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    printf("shield\n");
}
