/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#include "components//health_component.h"
#include "entity.h"

void set_combat_player(gc_entity *main_player, gc_entity *combat_player)
{
	struct health_component *h_cmp_main = \
GETCMP(main_player, health_component);
	struct health_component *h_cmp_combat = \
GETCMP(combat_player, health_component);

	if (!h_cmp_main || !h_cmp_combat)
		return;
	h_cmp_combat->health_max = h_cmp_main->health_max;
	h_cmp_combat->health = h_cmp_main->health;
	h_cmp_combat->dead = h_cmp_main->dead;
}