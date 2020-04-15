/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** selectors
*/

#include <stdbool.h>
#include <time.h>
#include <my.h>
#include "map_editor.h"
#include "engine.h"
#include "entity.h"

bool tile_select(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    manager->tile_mode = true;
    return (true);
}

bool vertex_select(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    manager->tile_mode = false;
    return (true);
}

bool save_map(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "vertex_component");
    struct vertex_component *map;
    time_t t;
    struct tm *tm;
    char save_file[1024];

    time(&t);
    tm = localtime(&t);
    my_strcpy(save_file, "map-");
    strftime(save_file + 4, sizeof(save_file) - 4, "%d-%m-%Y-%H:%M:%S", tm);
    my_strcat(save_file, ".gcmap");
    if (!list)
        return (false);
    map = GETCMP(list->data, vertex_component);
    my_printf("Saving the map to the file: %s\n", save_file);
    vertex_serialize(map, engine->scene, "tilemap.gcmap");
    return (true);
}