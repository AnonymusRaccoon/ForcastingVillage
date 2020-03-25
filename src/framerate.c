/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** framerate
*/

#include "entity.h"
#include "engine.h"
#include <malloc.h>
#include "utility.h"
#include "components/renderer.h"
#include "systems/sfml_renderer_system.h"
#include "limits.h"

static const int framerates[] = {
    30,
    60,
    120,
    INT_MAX
};

void framerate_set_text(gc_entity *entity, gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    struct renderer *renderer;
    char *framerate;

    if (!entity)
        return;
    renderer = GETCMP(entity, renderer);
    if (!rend || !renderer || renderer->type != GC_TXTREND)
        return;
    framerate = tostr(rend->framerate);
    free(((gc_text *)renderer->data)->text);
    ((gc_text *)renderer->data)->text = framerate;
}

bool framerate_down(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    int i = 2;

    if (!rend || rend->is_fullscreen)
        return (false);
    while (i > 0 && framerates[i] >= rend->framerate)
        i--;
    sfRenderWindow_setFramerateLimit(rend->window, framerates[i]);
    rend->framerate = framerates[i];
    framerate_set_text(engine->scene->get_entity(engine->scene, 52), engine);
    return (true);
}

bool framerate_up(gc_engine *engine, gc_entity *entity, gc_vector2 _)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    int i = 0;

    if (!rend || rend->is_fullscreen)
        return (false);
    while (framerates[i] <= rend->framerate)
        i++;
    if (framerates[i] == INT_MAX)
        return (true);
    sfRenderWindow_setFramerateLimit(rend->window, framerates[i]);
    rend->framerate = framerates[i];
    framerate_set_text(engine->scene->get_entity(engine->scene, 52), engine);
    return (true);
}