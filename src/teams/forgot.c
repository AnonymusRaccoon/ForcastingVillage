/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** forgot
*/

#include <stdbool.h>
#include "components/game_manager.h"
#include "components/teams_component.h"
#include "engine.h"

bool forgot_lmfao(gc_engine *engine, gc_entity *entity)
{
    gc_scene *scene = engine->scene;
    gc_list *li = scene->get_entity_by_cmp(scene, "game_manager");

    if (!li)
        return (false);
    GETCMP(li->data, game_manager)->happiness -= 5;
    GETCMP(li->data, game_manager)->stupidity -= 5;
    pm_clicked(engine, entity);
    return (true);
}

bool forgot_ok(gc_engine *engine, gc_entity *entity)
{
    gc_scene *scene = engine->scene;
    gc_list *li = scene->get_entity_by_cmp(scene, "game_manager");

    if (!li)
        return (false);
    GETCMP(li->data, game_manager)->happiness += 2;
    GETCMP(li->data, game_manager)->stupidity += 6;
    pm_clicked(engine, entity);
    return (true);
}