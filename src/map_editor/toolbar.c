/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** toolbar
*/

#include <stdbool.h>
#include "map_editor.h"
#include <utility.h>
#include "engine.h"
#include "entity.h"

bool up_down(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    manager->brush = MOVE;
    return (true);
}

bool reset(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    manager->brush = RESET;
    return (true);
}

bool rotate(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    manager->brush = ROTATE;
    return (true);
}

bool texture(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    manager->brush = TEXTURE;
    return (true);
}

bool switch_texture(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __)
{
    gc_scene *scene = engine->scene;
    gc_list *list = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *manager;
    void **data = scene->get_data(scene, "tiles", NULL);
    static int index = 0;
    void *next = NULL;

    if (!list)
        return (false);
    manager = GETCMP(list->data, map_manager_component);
    index++;
    if (data)
        next = data[index % (arraylen((const bool *)data) - 1)];
    manager->selected_texture = next;
    return (true);
}