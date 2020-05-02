/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_over
*/

#include <stdbool.h>
#include <components/controllable_component.h>
#include "engine.h"
#include "components/health_component.h"
#include "my.h"
#include "components/tag_component.h"

bool hide_game_over(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
	gc_scene *scene = engine->scene;
	gc_list *list = scene->get_entity_by_cmp(scene, "tag_component");
	gc_entity *player = scene->get_entity(scene, 50);
	struct health_component *hc;

	controllable_set_can_move(scene, true);
	if (!player)
		return (true);
	hc = GETCMP(player, health_component);
	if (!hc)
		return (true);
	hc->dead = false;
	hc->health = hc->health_max * 0.4;
	for (gc_list *li = list; li; li = li->next) {
		if (!my_strcmp(GETCMP(li->data, tag_component)->tag, "game_over"))
			((gc_entity *)li->data)->destroy(li->data, scene);
	}
	return (true);
}