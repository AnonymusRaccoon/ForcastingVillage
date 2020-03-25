/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#include "engine.h"
#include "setup.h"
#include "components/teams_component.h"
#include "components/isometry/map_manager_component.h"
#include "systems/teams_system.h"
#include <SFML/System.h>
#include "teams.h"
#include "callbacks.h"
#include "components/game_display.h"
#include "components/game_manager.h"
#include "systems/game_manager_system.h"
#include "map_interactions.h"
#include "my.h"

const struct callback callbacks[] = {
    {"start_button", &start_button},
    {"options", &options},
    {"goto_main_menu", &goto_main_menu},
    {"quit", &quit},
    {"fullscreen", &fullscreen},
    {"map_manage_click", &map_onclick},
    {"resolution_down", &resolution_down},
    {"resolution_up", &resolution_up},
    {"framerate_up", &framerate_up},
    {"framerate_down", &framerate_down},
    {"absent_check", &absent_check},
    {"absent_cross", &absent_cross},
    {"forgot_lmfao", &forgot_lmfao},
    {"forgot_ok", &forgot_ok},
    {"catch", &catch},
    {"toggle_pause", &toggle_pause},
    {"toggle_pause", &toggle_pause},
    {"tile_select", &tile_select},
    {"vertex_select", &vertex_select},
    {"up_down", &up_down},
    {"reset", &reset},
    {"rotate", &rotate},
    {"texture", &texture},
    {"switch_texture", &switch_texture},
    {NULL, NULL}
};

int register_customcmps(gc_engine *engine)
{
    engine->add_component(engine, &map_manager_component);
    engine->add_component(engine, &game_manager);
    engine->add_system(engine, new_system(&game_manager_system, engine));
    engine->add_component(engine, &game_display);
    engine->add_system(engine, &game_display_system);
    engine->add_component(engine, &teams_component);
    engine->add_system(engine, &teams_system);
    engine->finish_physics(engine);
    for (int i = 0; callbacks[i].func; i++)
        engine->add_callback(engine, my_strdup(callbacks[i].name), \
callbacks[i].func);
    return (0);
}

int create_game_scene(gc_engine *engine)
{
    gc_scene *scene;

    register_customcmps(engine);
    scene = scene_create(engine, "prefabs/mainmenu.gcprefab");
    if (!scene)
        return (-1);
    engine->change_scene(engine, scene);
    return (0);
}

int start_game(void)
{
    gc_engine *engine = engine_create();
    sfClock *clock = sfClock_create();

    if (!engine || engine_use_sfml(engine, "DPR tycoon", 60) < 0)
        return (ERROR);
    if (create_game_scene(engine) < 0)
        return (ERROR);
    while (engine->is_open(engine))
        engine->game_loop(engine, sfTime_asSeconds(sfClock_restart(clock)));
    engine->destroy(engine);
    sfClock_destroy(clock);
    return (0);
}