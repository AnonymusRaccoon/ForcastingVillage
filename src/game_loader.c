/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#include "engine.h"
#include "setup.h"
#include <SFML/System.h>
#include "components/dialog_holder.h"
#include "components/health_component.h"
#include "components/player_component.h"
#include "systems/combat_manager.h"
#include "components/combat_holder.h"
#include "components/attack_component.h"
#include "systems/map_movement_system.h"
#include "systems/game_manager_system.h"
#include "systems/controllers/keyboard_controller_system.h"
#include "components/map_movement.h"
#include "components/controllers/keyboard_controller.h"
#include "components/controllable_component.h"
#include "callbacks.h"
#include "components/game_manager.h"
#include "components/game_display.h"
#include "my.h"
#include "map_editor.h"
#include "components/xp_component.h"
#include "systems/game_over.h"
#include <malloc.h>

const struct callback callbacks[] = {
    {"start_button", &start_button},
    {"options", &options},
    {"goto_main_menu", &goto_main_menu},
    {"quit", &quit},
    {"fullscreen", &fullscreen},
    {"resolution_down", &resolution_down},
    {"resolution_up", &resolution_up},
    {"framerate_up", &framerate_up},
    {"framerate_down", &framerate_down},
    {"catch", &catch},
    {"toggle_pause", &toggle_pause},
    {"toggle_inventory", &toggle_inventory},
    {"action0", &dialog_input0},
    {"action1", &dialog_input1},
    {"action2", &dialog_input2},
    {"action3", &dialog_input3},
    {"hide_game_over", &hide_game_over},
    {"mia_heal", &mia_heal},
    {NULL, NULL}
};

const struct gc_data game_data[] = {
    {"input", "mia_heal", &mia_heal, NULL},
    {"input", "mia_save", &mia_save, NULL},
    {"input", "mia_fish", &mia_fish, NULL},
    {"dialog_callback", "mia_setup", &mia_setup, NULL},
    {NULL, NULL, NULL, NULL}
};

const struct callback map_editor_callbacks[] = {
    {"map_manage_click", &map_onclick},
    {"tile_select", &tile_select},
    {"vertex_select", &vertex_select},
    {"up_down", &up_down},
    {"reset", &reset},
    {"rotate", &rotate},
    {"texture", &texture},
    {"switch_texture", &switch_texture},
    {"save", &save_map},
    {NULL, NULL}
};

const struct gc_data attacks[] = {
    {"attack", "Uppercut", &uppercut, NULL},
    {"attack", "Fireball", &fireball, NULL},
    {"attack", "Water jet", &water_jet, NULL},
    {"attack", "Shield", &shield, NULL},
    {"attack", "Aerial attack", &enemy_attack, NULL},
    {"attack", "Spore attack", &enemy_attack, NULL},
    {"attack", "Sharp leaves", &enemy_attack, NULL},
    {"attack", "Spinning roots", &enemy_attack, NULL},
    {"attack", "Hypnosis", &enemy_attack, NULL},
    {"attack", "Water gun", &enemy_attack, NULL},
    {NULL, NULL, NULL,                         NULL}
};

void load_data(gc_scene *scene, const gc_data *datas)
{
    gc_data *data;

    for (int i = 0; datas[i].name; i++) {
        data = malloc(sizeof(*data));
        if (!data)
            return;
        data->name = my_strdup(datas[i].name);
        data->type = my_strdup(datas[i].type);
        data->custom = datas[i].custom;
        data->destroy = datas[i].destroy;
        LISTADD(scene->data, data);
    }
}

void load_attacks(gc_scene *scene)
{
    gc_list *li = scene->get_entity_by_cmp(scene, "attack_component");
    struct attack_component *att;

    load_data(scene, attacks);
    for (; li; li = li->next) {
        att = GETCMP(li->data, attack_component);
        for (int i = 0; att->attacks && att->attacks[i].name; i++)
            att->attacks[i].run = scene->get_data(scene, "attack", \
att->attacks[i].name);
    }
}

int register_customcmps(gc_engine *engine, bool map_editor)
{
    engine->add_component(engine, &controllable_component);
    engine->add_component(engine, &keyboard_controller);
    engine->add_component(engine, &map_movement);
    engine->add_system(engine, &map_movement_system);
    engine->add_component(engine, &dialog_holder);
    engine->add_system(engine, new_system(&dialog_manager, engine));
    engine->add_system(engine, new_system(&keyboard_controller_system, engine));
    engine->add_component(engine, &game_manager);
    engine->add_system(engine, new_system(&game_manager_system, engine));
    engine->add_component(engine, &map_manager_component);
    engine->add_component(engine, &game_display);
    engine->add_component(engine, &health_component);
    engine->add_system(engine, &game_display_system);
    engine->add_component(engine, &xp_component);
    engine->add_component(engine, &player_component);
    engine->add_component(engine, &attack_component);
    engine->add_component(engine, &combat_holder);
    engine->add_system(engine, new_system(&combat_manager, engine));
    engine->add_component(engine, &health_component);
    engine->finish_physics(engine);
    engine->add_dataloader(engine, "enemies", &enemies_dataloader);
    for (int i = 0; callbacks[i].func; i++)
        engine->add_callback(engine, my_strdup(callbacks[i].name), \
callbacks[i].func);
    if (map_editor)
        for (int i = 0; map_editor_callbacks[i].func; i++)
            engine->add_callback(engine, \
my_strdup(map_editor_callbacks[i].name), map_editor_callbacks[i].func);
    return (0);
}

int create_game_scene(gc_engine *engine, bool map_editor)
{
    gc_scene *scene;

    register_customcmps(engine, map_editor);
    scene = scene_create(engine, "prefabs/mainmenu.gcprefab");
    if (!scene)
        return (-1);
    engine->change_scene(engine, scene);
    return (0);
}

int start_game(bool map_editor)
{
    gc_engine *engine = engine_create();
    sfClock *clock = sfClock_create();

    if (!engine || engine_use_sfml(engine, "Forecasting village", 60) < 0)
        return (ERROR);
    if (create_game_scene(engine, map_editor) < 0)
        return (ERROR);
    while (engine->is_open(engine))
        engine->game_loop(engine, sfTime_asSeconds(sfClock_restart(clock)));
    engine->destroy(engine);
    sfClock_destroy(clock);
    return (0);
}