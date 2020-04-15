/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** xp methods
*/

#include "components/xp_component.h"
#include "engine.h"

void add_xp(struct xp_component *this, gc_engine *engine, \
unsigned int amount)
{
    if (this->full)
        return;
    this->xp += amount;
    if (this->xp >= 100)
        this->full = true;
    engine->trigger_event(engine, "add_xp", this->xp, amount);
}

void rem_xp(struct xp_component *this, gc_engine *engine, \
unsigned int amount)
{
    this->xp -= amount;
    engine->trigger_event(engine, "rem_xp", this->xp, amount);
}