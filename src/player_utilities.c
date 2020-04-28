/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#include <systems/combat_manager.h>
#include "components//health_component.h"
#include "entity.h"

void set_combat_player(gc_engine *engine, gc_entity *player, gc_entity *cbt)
{
	struct health_component *main = GETCMP(player, health_component);
	struct health_component *combat = GETCMP(cbt, health_component);
    struct combat_manager *this = GETSYS(engine, combat_manager);

    this->last_attack = NULL;
    this->last_damage = 0;
	if (!main || !combat)
		return;
    combat->health_max = main->health_max;
    combat->health = main->health;
    combat->dead = main->dead;

}