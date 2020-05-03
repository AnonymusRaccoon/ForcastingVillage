/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** particule_system
*/

#include "engine.h"
#include "sprite.h"
#include "systems/sfml_renderer_system.h"
#include "sfml_renderer.h"
#include "components/particule_component.h"
#include "components/map_linker.h"
#include "system.h"

void create_particule(struct particule *particule, int lifetime, \
void *texture, gc_vector2 pos)
{
	if (!particule || !particule->sprite)
		return;
	particule->lifetime = lifetime;
	particule->sprite->texture = texture;
	particule->sprite->pos = pos;
	particule->sprite->rect = (gc_int_rect){16, 16,0,0};
	particule->sprite->scale = (gc_vector2){0.2, 0.2};
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
		tc->position = pm->particules[i].sprite->pos;
		sfmlrenderer_draw_texture(engine, entity, pm->particules[i].sprite, dt);
	}
	tc->position = player_pos;
}

static void update_entity(gc_engine *engine, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    float dtime = va_arg(args, double);
	struct map_linker *ml = GETCMP(entity, map_linker);
	struct particule_component *cmp = GETCMP(entity, particule_component);
	struct transform_component *tc = GETCMP(entity, transform_component);

	if (!ml || !tc || !cmp)
		return;
	//ml->tile->texture
	for (int i = 0; i < cmp->nb_max_particules; i++) {
		cmp->particules[i].lifetime -= (cmp->particules[i].lifetime) ? 1 : 0;
		if (!cmp->particules[i].lifetime) {
			create_particule(&cmp->particules[i], cmp->lifetime, cmp->texture, tc->position);
		}
	}
	particule_draw(engine, entity, dtime);
}

void ctr(void *system, va_list args)
{
    gc_engine *engine = va_arg(args, gc_engine *);

    engine->add_event_listener(engine, "linked_entity_draw",&update_entity);
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