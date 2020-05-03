/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** particule_system
*/

#include "engine.h"
#include "sprite.h"
#include "sfml_renderer.h"
#include "components/particule_component.h"
#include <stdlib.h>

void create_particule(struct particule *particule, int lifetime, \
void *texture, gc_vector2 pos)
{
    if (!particule || !particule->sprite)
        return;
    pos.x += (rand() % 2) ? rand() % 20 : (rand() % 20) * -1;
    pos.y += (rand() % 2) ? rand() % 20 : (rand() % 20) * -1;
    particule->lifetime = lifetime;
    particule->sprite->texture = texture;
    particule->sprite->pos = (gc_vector2){pos.x, pos.y};
    particule->sprite->rect = (gc_int_rect){16, 16,0,0};
    particule->sprite->scale = (gc_vector2){0.1, 0.1};
}

void particule_draw(gc_engine *engine, gc_entity *entity, float dt)
{
    struct particule_component *pm = GETCMP(entity, particule_component);
    struct transform_component *tc = GETCMP(entity, transform_component);
    gc_vector2 player_pos;

    if (!pm || !entity || !tc)
        return;
    player_pos = tc->position;
    for (int i = 0; i < pm->nb_max_particules; i++) {
        if (!pm->particules[i].sprite || !pm->particules[i].sprite->texture)
            continue;
        if (!pm->particules[i].lifetime)
            continue;
        tc->position = pm->particules[i].sprite->pos;
        sfmlrenderer_draw_texture(engine, entity, \
pm->particules[i].sprite, dt);
    }
    tc->position = player_pos;
}