/*
** EPITECH PROJECT, 2020
** Myrpg
** File description:
** sound
*/

#include "entity.h"
#include "engine.h"
#include <malloc.h>
#include <SFML/Audio.h>
#include "utility.h"
#include "components/renderer.h"
#include "systems/sfml_renderer_system.h"
#include "limits.h"

void sound_set_text(gc_entity *entity, gc_engine *engine, float vol)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    struct renderer *renderer;
    char volume[10];

    if (!entity)
        return;
    renderer = GETCMP(entity, renderer);
    if (!rend || !renderer || renderer->type != GC_TXTREND)
        return;
    snprintf(volume, 10, "%.0f", vol);
    ((gc_text *)renderer->data)->text = volume;
}

bool sound_down(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    float vol = sfListener_getGlobalVolume();
    
    vol = MAX(vol - 5, 0);
    sfListener_setGlobalVolume(vol);
    sound_set_text(engine->scene->get_entity(engine->scene, 53), engine, vol);
    return (true);
}

bool sound_up(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __)
{
    float vol = sfListener_getGlobalVolume();

    vol = MIN(vol + 5, 100);
    sfListener_setGlobalVolume(vol);
    sound_set_text(engine->scene->get_entity(engine->scene, 53), engine, vol);
    return (true);
}