/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#include <systems/combat_manager.h>
#include <components/player_component.h>
#include "components//health_component.h"
#include "entity.h"

void set_combat_player(gc_engine *engine, gc_entity *player, gc_entity *cbt)
{
	struct health_component *main;
	struct health_component *combat;
	struct player_component *minv;
	struct player_component *inv;
    struct combat_manager *this;

    if (!engine || !player || !cbt)
		return;
	main = GETCMP(player, health_component);
	combat = GETCMP(cbt, health_component);
	this = GETSYS(engine, combat_manager);
    minv = GETCMP(player, player_component);
    inv = GETCMP(cbt, player_component);
    this->last_attack = NULL;
	if (!main || !combat || !inv || !minv)
		return;
    combat->health_max = main->health_max;
    combat->health = main->health;
    combat->dead = main->dead;
    for (int i = 0; i < 4; i++)
        inv->inventory_upgrades[i] = minv->inventory_upgrades[i];
}