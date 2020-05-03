/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particule_component.c
*/

#include "xml.h"
#include "components/particule_component.h"
#include "components/map_linker.h"
#include "systems/particule_system.h"
#include "component.h"
#include <malloc.h>
#include "utility.h"
#include "tile.h"

static void ctr(void *component, va_list args)
{
	struct particule_component *cmp = (struct particule_component *)\
component;
	gc_sprite *sprites;

	cmp->type = va_arg(args, int);
	cmp->nb_max_particules = va_arg(args, int);
	cmp->lifetime = va_arg(args, int);
	cmp->texture = va_arg(args, void *);
	cmp->particules = malloc(sizeof(struct particule_component) * \
(cmp->nb_max_particules + 1));
	sprites = malloc(sizeof(gc_sprite) * (cmp->nb_max_particules + 1));
	if (!cmp->particules || !sprites)
		return;
	for (int i = 0; i < cmp->nb_max_particules; i++) {
		cmp->particules[i].sprite = &sprites[i];
		create_particule(&cmp->particules[i], i * 20, NULL, \
(gc_vector2){0, 0});
	}
}

static void fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
	struct particule_component *cmp = (struct particule_component *)\
component;
	struct map_linker *ml = GETCMP(entity, map_linker);
	gc_sprite *sprites;

	if (!ml) {
		my_printf("No linker\n");
		return;
	}
	cmp->type = xml_getintprop(n, "type");
	cmp->nb_max_particules = xml_getintprop(n, "nb_particules_max");
	cmp->texture = scene->get_data(scene, "sprite", xml_getproperty(n, "texture"));
	cmp->lifetime = xml_getintprop(n, "lifetime");
	cmp->particules = malloc(sizeof(struct particule_component) * \
(cmp->nb_max_particules + 1));
	sprites = malloc(sizeof(gc_sprite) * (cmp->nb_max_particules + 1));
	if (!cmp->particules || !sprites)
		return;
	for (int i = 0; i < cmp->nb_max_particules; i++) {
		cmp->particules[i].sprite = &sprites[i];
		create_particule(&cmp->particules[i], i * 20, NULL, \
(gc_vector2){0, 0});
	}
}

static void dtr(void *component)
{
	struct particule_component *cmp = (struct particule_component *)\
component;
	if (!cmp->particules)
		return;
	free(cmp->particules[0].sprite);
	free(cmp->particules);
}

static char *serialize(void *component)
{
	(void)component;
	return (NULL);
}

const struct particule_component particule_component = {
	base: {
		name: "particule_component",
		size: sizeof(struct particule_component),
		dependencies: (char *[]){
			"transform_component",
			"map_linker",
			NULL
		},
		ctr: &ctr,
		fdctr: &fdctr,
		dtr: &dtr,
		serialize: &serialize,
		destroy: &component_destroy
	}
};