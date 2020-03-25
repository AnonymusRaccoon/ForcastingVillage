/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** absent
*/

#include <stdbool.h>
#include "components/game_manager.h"
#include <stdlib.h>
#include "components/teams_component.h"
#include "engine.h"

bool absent_check(gc_engine *engine, gc_entity *entity)
{
    gc_scene *scene = engine->scene;
    gc_list *li = scene->get_entity_by_cmp(scene, "game_manager");

    if (!li)
        return (false);
    GETCMP(li->data, game_manager)->happiness += 3;
    GETCMP(li->data, game_manager)->stupidity += random() % 5;
    pm_clicked(engine, entity);
    return (true);
}

bool absent_cross(gc_engine *engine, gc_entity *entity)
{
    gc_scene *scene = engine->scene;
    gc_list *li = scene->get_entity_by_cmp(scene, "game_manager");

    if (!li)
        return (false);
    GETCMP(li->data, game_manager)->happiness -= 3;
    GETCMP(li->data, game_manager)->stupidity -= random() % 5;
    pm_clicked(engine, entity);
    return (true);
}