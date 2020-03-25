/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** options
*/

#include "engine.h"
#include "setup.h"
#include <stdbool.h>
#include "sprite.h"
#include <stdio.h>
#include <malloc.h>
#include "my.h"
#include "components/renderer.h"
#include "systems/sfml_renderer_system.h"
#include <limits.h>

static const gc_vector2i resolutions[] = {
    {800, 600},
    {1280, 720},
    {1920, 1080},
    {INT_MAX, INT_MAX}
};

int checkbox_update(gc_scene *s, gc_entity *entity, bool checked)
{
    struct renderer *renderer;
    char *sprite = checked ? "check" : "cross";

    if (!entity)
        return (-1);
    renderer = GETCMP(entity, renderer);
    if (!renderer || renderer->type != GC_TEXTUREREND)
        return (-1);

    ((gc_sprite *)renderer->data)->texture = s->get_data(s, "sprite", sprite);
    return (0);
}

void resolution_set_text(gc_entity *entity, gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    struct renderer *renderer;
    char *resolution = malloc(sizeof(char) * 10);

    if (!entity)
        return;
    renderer = GETCMP(entity, renderer);
    if (!rend || !renderer || renderer->type != GC_TXTREND)
        return;
    snprintf(resolution, 10, "%ix%i", rend->resolution.x, rend->resolution.y);
    if (rend->is_fullscreen)
        my_strcpy(resolution, "auto");
    free(((gc_text *)renderer->data)->text);
    ((gc_text *)renderer->data)->text = resolution;
}

bool fullscreen(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    if (!rend)
        return (false);
    rend->is_fullscreen = !rend->is_fullscreen;
    if (checkbox_update(engine->scene, entity, rend->is_fullscreen) < 0)
        return (false);
    sfRenderWindow_destroy(rend->window);
    if (rend->is_fullscreen)
        rend->window = sfRenderWindow_create(sfVideoMode_getDesktopMode(), \
"My3D", sfFullscreen | sfClose, NULL);
    else
        rend->window = sfRenderWindow_create((sfVideoMode){rend->resolution.x, \
rend->resolution.y, 32}, "My3D", sfDefaultStyle, NULL);
    resolution_set_text(engine->scene->get_entity(engine->scene, 51), engine);
    return (true);
}

bool resolution_down(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    int i = 2;

    if (!rend || rend->is_fullscreen)
        return (false);
    while (i > 0 && resolutions[i].x >= rend->resolution.x)
        i--;
    sfRenderWindow_setSize(rend->window, (sfVector2u){
        resolutions[i].x,
        resolutions[i].y
    });
    rend->resolution = resolutions[i];
    resolution_set_text(engine->scene->get_entity(engine->scene, 51), engine);
    return (true);
}

bool resolution_up(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    int i = 0;

    if (!rend || rend->is_fullscreen)
        return (false);
    while (resolutions[i].x <= rend->resolution.x)
        i++;
    if (resolutions[i].x == INT_MAX)
        return (true);
    sfRenderWindow_setSize(rend->window, (sfVector2u){
        resolutions[i].x,
        resolutions[i].y
    });
    rend->resolution = resolutions[i];
    resolution_set_text(engine->scene->get_entity(engine->scene, 51), engine);
    return (true);
}