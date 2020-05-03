/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** particule_system
*/

#include "engine.h"
#include "sprite.h"
#include "sfml_renderer.h"
#include "components/controllable_component.h"
#include "components/particule_component.h"
#include "components/map_linker.h"
#include "systems/particule_system.h"
#include "system.h"
#include <stdlib.h>

void update_entity_type_one(gc_engine *engine, gc_entity *entity, \
struct particule_component *cmp, float dtime)
{
    struct map_linker *ml = GETCMP(entity, map_linker);
    struct transform_component *tc = GETCMP(entity, transform_component);
    struct controllable_component *cc = GETCMP(entity, controllable_component);

    if (!ml || !tc || !cmp || !cc)
        return;
    for (int i = 0; i < cmp->nb_max_particules; i++) {
        cmp->particules[i].lifetime -= (cmp->particules[i].lifetime) ? 1 : 0;
        if (!cmp->particules[i].lifetime && \
(cc->movement_x || cc->movement_y) && \
(!i || cmp->particules[i - 1].lifetime == cmp->lifetime - 20)) {
            create_particule(&cmp->particules[i], cmp->lifetime, \
cmp->texture, tc->position);
        }
    }
    particule_draw(engine, entity, dtime);
}

void update_entity_type_two(gc_engine *engine, gc_entity *entity, \
struct particule_component *cmp, float dtime)
{
    struct map_linker *ml = GETCMP(entity, map_linker);
    struct transform_component *tc = GETCMP(entity, transform_component);
    gc_vector2 sprite_pos;

    if (!ml || !tc || !cmp || !cmp->particules || !cmp->particules[0].sprite)
        return;
    sprite_pos = (gc_vector2){tc->position.x, tc->position.y + 50};
    for (int i = 0; i < cmp->nb_max_particules; i++) {
        cmp->particules[i].lifetime -= (cmp->particules[i].lifetime) ? 1 : 0;
        cmp->particules[i].sprite->pos.y += 1;
        if (!cmp->particules[i].lifetime && \
(!i || cmp->particules[i - 1].lifetime == cmp->lifetime - 20)) {
            create_particule(&cmp->particules[i], cmp->lifetime, \
cmp->texture, sprite_pos);
        }
    }
    particule_draw(engine, entity, dtime);
}

static void update_entity(gc_engine *engine, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    float dtime = va_arg(args, double);
    struct particule_component *cmp = GETCMP(entity, particule_component);

    if (!cmp)
        return;
    switch (cmp->type) {
    case 1:
        return (update_entity_type_one(engine, entity, cmp, dtime));
    case 2:
        return (update_entity_type_two(engine, entity, cmp, dtime));
    default:
        break;
    }
}

void ctr(void *system, va_list args)
{
    gc_engine *engine = va_arg(args, gc_engine *);

    engine->add_event_listener(engine, "linked_entity_draw", &update_entity);
}

const struct gc_system particule_system = {
    name: "particule_system",
    component_name: "particule_component",
    size: sizeof(gc_system),
    ctr: &ctr,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: NULL,
    destroy: &system_destroy
};