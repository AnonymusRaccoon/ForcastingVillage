/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_manager.c
*/

#include <components/map_linker.h>
#include "my.h"
#include "components/dialog_holder.h"
#include "components/tag_component.h"
#include "prefab.h"
#include "engine.h"
#include "tile.h"

void load_dialog(gc_engine *engine, gc_entity *player)
{
    struct map_linker *link = GETCMP(player, map_linker);

    if (!link || !link->tile->type || my_strcmp(link->tile->type, "dialog"))
        return;
    prefab_load(engine, "prefabs/dialog.gcprefab");
}

static void check_for_dialog(gc_engine *engine, va_list args)
{
    struct dialog_manager *dima = GETSYS(engine, dialog_manager);
    gc_keybindings key = va_arg(args, gc_keybindings);
    gc_scene *scene = engine->scene;
    gc_list *list;
    gc_entity *entity = scene->get_entity(scene, 50);

    if (key != SPACE || !entity)
        return;
    dima->is_dialog_open = !dima->is_dialog_open;
    if (dima->is_dialog_open) {
        load_dialog(engine, entity);
        return;
    }
    list = scene->get_entity_by_cmp(scene, "tag_component");
    for (gc_list *li = list; li; li = li->next) {
        if (!my_strcmp(GETCMP(li->data, tag_component)->tag, "dialog"))
            ((gc_entity *)li->data)->destroy(li->data, scene);
    }
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);
    struct dialog_manager *dima = (struct dialog_manager *)system;

    engine->add_event_listener(engine, "key_pressed", &check_for_dialog);
    dima->is_dialog_open = false;
}

static void dtr(void *system, gc_engine *engine)
{
    engine->remove_event_listener(engine, "key_pressed", &check_for_dialog);
}

const struct dialog_manager dialog_manager = {
    base: {
        name: "dialog_manager",
        component_name: "dialog_holder",
        size: sizeof(gc_system),
        ctr: &ctr,
        dtr: &dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &update_entity,
        destroy: &system_destroy
    },
};