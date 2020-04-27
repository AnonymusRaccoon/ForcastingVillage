/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_manager.c
*/

#include <systems/combat_manager.h>
#include <tile.h>
#include <components/player_component.h>
#include <stdlib.h>
#include "engine.h"
#include "my.h"
#include "components/dialog_holder.h"
#include "enemy.h"
#include "player_utilities.h"

void entity_moved(gc_engine *engine, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    struct tile *tile = va_arg(args, struct tile *);
    struct player_component *cmp = GETCMP(entity, player_component);

    if (!cmp)
        return;
    if (tile->type && my_strcmp(tile->type, "combat"))
        combat_start(engine, NULL);
    if (random() % 100 < cmp->fight_rate)
        combat_start(engine, NULL);
}

void dialog_ended(gc_engine *engine, va_list args)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    gc_entity *player_combat = this->game_scene->get_entity(this->game_scene, 50);

    if (!this->current_enemy || !player || ! player_combat)
        return;
	set_combat_player(player_combat, player);
    engine->trigger_event(engine, "combat_ended", this->current_enemy);
    this->current_enemy = NULL;
    engine->change_scene(engine, this->game_scene);
    this->game_scene = NULL;
    this->state = ATTACK;
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct combat_manager *this = system;
    gc_scene *scene = engine->scene;
    gc_list *li = scene->get_entity_by_cmp(scene, "dialog_holder");
    struct dialog_holder *dialog;

    if (!li)
        return;
    dialog = GETCMP(li->data, dialog_holder);
    switch (this->state) {
    case ATTACK:
        return (show_attacks(this, dialog, scene, engine));
    case DEFEND:
        return (defend(this, dialog, scene, engine));
    case ATTACKING:
    case DEFENDING:
    case IDLE:
        break;
    }
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);
    struct combat_manager *this = (struct combat_manager *)system;

    this->game_scene = NULL;
    this->state = ATTACK;
    engine->add_event_listener(engine, "entity_moved", &entity_moved);
    engine->add_event_listener(engine, "dialog_ended", &dialog_ended);
}

static void dtr(void *system, gc_engine *engine)
{
    struct combat_manager *this = system;

    engine->remove_event_listener(engine, "entity_moved", &entity_moved);
    engine->remove_event_listener(engine, "dialog_ended", &dialog_ended);
    if (this->game_scene)
        scene_destroy(this->game_scene);
}

const struct combat_manager combat_manager = {
    base: {
        name: "combat_manager",
        component_name: "combat_holder",
        size: sizeof(struct combat_manager),
        ctr: &ctr,
        dtr: &dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &update_entity,
        destroy: &system_destroy
    },
};