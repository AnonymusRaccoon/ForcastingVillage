/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particule_component.c
*/

#ifndef MY_RPG_PARTICULE_COMPONENT_H
#define MY_RPG_PARTICULE_COMPONENT_H

#include <stdbool.h>
#include "sprite.h"
#include "component.h"

struct particule
{
	unsigned int lifetime;
	gc_sprite *sprite;
};

struct particule_component
{
	gc_component base;
	int type;
	unsigned int lifetime;
	int nb_max_particules;
	void *texture;
	struct particule *particules;
};



extern const struct particule_component particule_component;

#endif //MY_RPG_PARTICULE_COMPONENT_H
