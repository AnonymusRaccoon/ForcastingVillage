/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** main_menu
*/

#include <systems/sfml_renderer_system.h>
#include "engine.h"
#include "scene.h"
#include "setup.h"
#include "my.h"

bool start_button(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    gc_scene *scene = scene_create(engine, "prefabs/game.gcprefab");
    if (!scene) {
        engine->should_close = true;
        my_printf("The game scene couldn't be loaded.\n");
        return (true);
    }
    engine->change_scene(engine, scene);
    return (true);
}

bool options(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    gc_scene *scene = scene_create(engine, "prefabs/options.gcprefab");
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    if (!scene) {
        engine->should_close = true;
        my_printf("The option scene couldn't be loaded.\n");
        return (true);
    }
    engine->change_scene(engine, scene);
    entity = engine->scene->get_entity(engine->scene, 50);
    if (rend)
        checkbox_update(engine->scene, entity, rend->is_fullscreen);
    entity = engine->scene->get_entity(engine->scene, 51);
    resolution_set_text(entity, engine);
    entity = engine->scene->get_entity(engine->scene, 52);
    framerate_set_text(entity, engine);
    return (true);
}

bool goto_main_menu(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    gc_scene *scene = scene_create(engine, "prefabs/mainmenu.gcprefab");
    if (!scene) {
        engine->should_close = true;
        my_printf("The option scene couldn't be loaded.\n");
        return (true);
    }
    engine->change_scene(engine, scene);
    return (true);
}

bool quit(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    engine->should_close = true;
    return (true);
}

bool catch(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    return (true);
}