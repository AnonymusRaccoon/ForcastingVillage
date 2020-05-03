/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** game_manager_system
*/

#include <components/tag_component.h>
#include <systems/sfml_renderer_system.h>
#include <enemy.h>
#include <components/xp_component.h>
#include "my.h"
#include "prefab.h"
#include "keybindings.h"
#include "system.h"
#include "components/game_manager.h"
#include "systems/game_manager_system.h"
#include "systems/inventory.h"

bool toggle_pause(gc_engine *engine)
{
    gc_scene *scene = engine->scene;
    gc_list *list;

    scene->is_paused = !scene->is_paused;
    if (scene->is_paused) {
        prefab_load(engine,"prefabs/pause.gcprefab");
        return (true);
    }
    list = scene->get_entity_by_cmp(scene, "tag_component");
    for (gc_list *li = list; li; li = li->next) {
        if (!my_strcmp(GETCMP(li->data, tag_component)->tag, "pause"))
            ((gc_entity *)li->data)->destroy(li->data, scene);
    }
    return (true);
}

static void key_pressed(gc_engine *engine, va_list args)
{
    gc_keybindings key = va_arg(args, gc_keybindings);

    if (key == ESCAPE)
		toggle_pause(engine);
    if (key == KEY_E)
    	toggle_inventory(engine);
}

static void combat_ended(gc_engine *engine, va_list args)
{
    struct enemy *enemy = va_arg(args, struct enemy *);
    bool has_won = va_arg(args, int);
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct xp_component *xp;

    if (!player || !has_won)
        return;
    xp = GETCMP(player, xp_component);
    if (!xp)
        return;
    xp_add(xp, engine, 10);
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);
    struct game_manager_system *this = system;

    engine->add_event_listener(engine, "key_pressed", &key_pressed);
    engine->add_event_listener(engine, "combat_ended", &combat_ended);
    this->has_message = false;
    this->is_inventory = false;
}

static void dtr(void *system, gc_engine *engine)
{
    engine->remove_event_listener(engine, "key_pressed", &key_pressed);
    engine->remove_event_listener(engine, "combat_ended", &combat_ended);
}

const struct game_manager_system game_manager_system = {
	base : {
		name: "game_manager_system",
		component_name: "game_manager",
		size: sizeof(struct game_manager_system),
		ctr: &ctr,
		dtr: &dtr,
		check_dependencies: &system_check_dependencies,
		update_entity: NULL,
		destroy: &system_destroy
	},
    is_inventory: false
};