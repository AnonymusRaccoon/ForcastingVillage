/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** fireball.c
*/

#include <systems/combat_manager.h>
#include <systems/game_manager_system.h>
#include <stdlib.h>
#include <utility.h>
#include <components/player_component.h>
#include "components/health_component.h"
#include "engine.h"
#include "components/renderer.h"

void uppercut(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    struct player_component *inv = GETCMP(from, player_component);
    struct health_component *enemy_health = GETCMP(enemy, health_component);
    struct renderer *rend = GETCMP(from, renderer);
    int max;

    if (this->last_attack && my_strcmp(this->last_attack, "uppercut"))
        max = 20 - this->last_damage;
    else
        max = 10;
    this->last_damage = MAX(MIN(random() % max, 10), 0);
    this->last_damage *= inv && inv->inventory_upgrades[2] ? 1 : 1.5;
    this->last_attack = "uppercut";
    rem_health(enemy_health, engine, this->last_damage);
    if (rend)
        rend_set_anim(rend, "uppercut");
}

void water_jet(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    struct player_component *inv = GETCMP(from, player_component);
    struct health_component *enemy_health = GETCMP(enemy, health_component);
    struct renderer *rend = GETCMP(from, renderer);
    int max;

    if (this->last_attack && my_strcmp(this->last_attack, "water_jet"))
        max = 20 - this->last_damage;
    else
        max = 10;
    this->last_damage = MAX(MIN(random() % max, 10), 0);
    this->last_damage *= inv && inv->inventory_upgrades[1] ? 1 : 1.5;
    this->last_attack = "water_jet";
    rem_health(enemy_health, engine, this->last_damage);
    if (rend)
        rend_set_anim(rend, "water_jet");
}

void fireball(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    struct player_component *inv = GETCMP(from, player_component);
    struct health_component *enemy_health = GETCMP(enemy, health_component);
    struct renderer *rend = GETCMP(from, renderer);
    int max;

    if (this->last_attack && my_strcmp(this->last_attack, "fireball"))
        max = 20 - this->last_damage;
    else
        max = 10;
    this->last_damage = MAX(MIN(random() % max, 10), 0);
    this->last_damage *= inv && inv->inventory_upgrades[0] ? 1 : 1.5;
    this->last_attack = "fireball";
    rem_health(enemy_health, engine, this->last_damage);
    if (rend)
        rend_set_anim(rend, "fireball");
}

void shield(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    struct player_component *inv = GETCMP(from, player_component);
    struct renderer *rend = GETCMP(from, renderer);

    this->last_damage = 50;
    this->last_damage *= inv && inv->inventory_upgrades[3] ? 1 : 1.5;
    this->last_attack = "shield";
    if (rend)
        rend_set_anim(rend, "shield");
}

void enemy_attack(gc_engine *engine, gc_entity *from, gc_entity *enemy)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    struct health_component *enemy_health = GETCMP(enemy, health_component);
    struct renderer *rend = GETCMP(from, renderer);
    int max = 10 - this->last_enemy_damage;

    this->last_enemy_damage = MAX(MIN(random() % max, 10), 0);
    if (this->last_attack && !my_strcmp(this->last_attack, "shield"))
        add_health(enemy_health, engine, 5);
    rem_health(enemy_health, engine, this->last_enemy_damage);
    if (rend)
        rend_set_anim(rend, "attack");
}
