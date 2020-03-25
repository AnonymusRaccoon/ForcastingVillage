/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** game_manager_system
*/

#include <components/tag_component.h>
#include <systems/sfml_renderer_system.h>
#include "my.h"
#include "prefab.h"
#include "keybindings.h"
#include "system.h"
#include "components/game_manager.h"

bool toggle_pause(gc_engine *engine)
{
    gc_scene *scene = engine->scene;
    gc_list *list;

    scene->is_paused = !scene->is_paused;
    if (scene->is_paused) {
        prefab_load(engine, "prefabs/pause.gcprefab");
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
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct game_manager *manager = GETCMP(entity, game_manager);
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    gc_scene *gameover_scene = NULL;

    if (manager->happiness <= 0)
        gameover_scene = scene_create(engine, "prefabs/go/happiness.gcprefab");
    if (manager->stupidity >= 100)
        gameover_scene = scene_create(engine, "prefabs/go/stupidity.gcprefab");

    if (gameover_scene)
        engine->change_scene(engine, gameover_scene);
    if (engine->is_keypressed(sfKeyLeft))
        sfView_move(rend->view, (sfVector2f){-10, 0});
    if (engine->is_keypressed(sfKeyRight))
        sfView_move(rend->view, (sfVector2f){10, 0});
    if (engine->is_keypressed(sfKeyDown))
        sfView_move(rend->view, (sfVector2f){0, 10});
    if (engine->is_keypressed(sfKeyUp))
        sfView_move(rend->view, (sfVector2f){0, -10});
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);

    engine->add_event_listener(engine, "key_pressed", &key_pressed);
}

const gc_system game_manager_system = {
    name: "game_cycle",
    component_name: "game_manager",
    size: sizeof(gc_system),
    ctr: ctr,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &system_destroy
};