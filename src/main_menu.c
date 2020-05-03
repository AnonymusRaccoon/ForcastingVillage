/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** main_menu
*/

#include <systems/combat_manager.h>
#include <systems/game_manager_system.h>
#include "systems/sfml_renderer_system.h"
#include "components/dialog_holder.h"
#include "components/dialog_holder.h"
#include "engine.h"
#include "prefab.h"
#include "scene.h"
#include "setup.h"
#include "my.h"

extern int entity_next_id;

bool start_button(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    gc_scene *scene;

    prefab_load(engine, "prefabs/loading.gcprefab");
    engine->game_loop(engine, 0);
    scene = scene_new(engine);
    load_data(scene, game_data);
    if (!(scene = scene_parse_xml(scene, engine, "prefabs/game.gcprefab"))) {
        engine->should_close = true;
        my_printf("The game scene couldn't be loaded.\n");
        return (true);
    }
    engine->change_scene(engine, scene);
    if (prefab_load(engine, "prefabs/player.gcprefab") < 0
    || prefab_load(engine, "prefabs/map_entities.gcprefab") < 0)
        my_printf("Could not load entites.\n");
    else if (engine->get_callback(engine, "map_manage_click"))
        if (prefab_load(engine, "prefabs/editor_ui.gcprefab") < 0)
            my_printf("Couldn't load the map editor's ui.\n");
    GETSYS(engine, dialog_manager)->dialog_id = -1;
    entity_next_id = 0;
    return (true);
}

bool options(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    gc_scene *scene = scene_create(engine, "prefabs/options.gcprefab");
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    if (!scene) {
        engine->should_close = true;
        my_printf("The option scene couldn't be loaded.\n");
        return (true);
    }
    GETSYS(engine, game_manager_system)->game_scene = engine->scene;
    engine->scene = NULL;
    engine->change_scene(engine, scene);
    entity = engine->scene->get_entity(engine->scene, 50);
    if (rend)
        checkbox_update(engine->scene, entity, rend->is_fullscreen);
    entity = engine->scene->get_entity(engine->scene, 51);
    resolution_set_txt(entity, engine, 0);
    entity = engine->scene->get_entity(engine->scene, 52);
    framerate_set_text(entity, engine, 0);
    entity = engine->scene->get_entity(engine->scene, 53);
    sound_set_text(entity, engine, -1);
    return (true);
}

bool goto_main_menu(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    gc_scene *scene = GETSYS(engine, game_manager_system)->game_scene;

    if (!scene)
        scene = scene_create(engine, "prefabs/mainmenu.gcprefab");
    GETSYS(engine, game_manager_system)->game_scene = NULL;
    if (!scene) {
        engine->should_close = true;
        my_printf("The option scene couldn't be loaded.\n");
        return (true);
    }
    engine->change_scene(engine, scene);
    return (true);
}

bool quit(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    engine->should_close = true;
    return (true);
}

bool catch(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    return (true);
}