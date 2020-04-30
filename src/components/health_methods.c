/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** health component
*/

#include "components/health_component.h"
#include "engine.h"

void rem_health(struct health_component *this, gc_engine *engine, \
unsigned int amount)
{
    if (this->dead)
        return;
    this->health -= amount;
	if (this->health < 0)
		this->health = 0;
    engine->trigger_event(engine, "rem_health", this->health, amount);
    if (this->health <= 0)
        this->dead = true;
}

void add_health(struct health_component *this, gc_engine *engine, \
unsigned int amount)
{
    if (this->dead)
        return;
    this->health += amount;
    if (this->health > this->health_max)
        this->health = this->health_max;
    engine->trigger_event(engine, "add_health", this->health, amount);
}