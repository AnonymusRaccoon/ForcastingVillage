/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** inventory
*/

#include "list.h"
#include "scene.h"
#include "sprite.h"
#include "prefab.h"
#include "components/renderer.h"
#include "components/tag_component.h"
#include "my.h"

void display_inventory_object(gc_scene *scene, struct renderer *rend, int nb)
{
	char *textures[5] = {"empty_slot", "slot_1", "slot_2", "slot_3", "slot_4"};
	if (false)
		nb = 0;
	((gc_sprite *)rend->data)->texture = scene->get_data(scene, "sprite", textures[nb]);
}

bool toggle_inventory(gc_engine *engine)
{
	gc_scene *scene = engine->scene;
	gc_list *list;

	scene->is_paused = !scene->is_paused;
	if (scene->is_paused) {
		prefab_load(engine, "prefabs/inventory.gcprefab");
		return (true);
	}
	list = scene->get_entity_by_cmp(scene, "tag_component");
	for (gc_list *li = list; li; li = li->next) {
		if (!my_strcmp(GETCMP(li->data, tag_component)->tag, "inventory"))
			((gc_entity *)li->data)->destroy(li->data, scene);
	}
	return (true);
}