/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** xp methods
*/

#include "components/xp_component.h"
#include "engine.h"

void xp_add(struct xp_component *this, gc_engine *engine, \
unsigned int amount)
{
    if (this->full)
        return;
    this->xp += amount;
    if (this->xp >= 100) {
        this->full = true;
        this->xp = 100;
    }
    engine->trigger_event(engine, "xp_add", this->xp, amount);
}

void xp_rem(struct xp_component *this, gc_engine *engine, \
unsigned int amount)
{
    this->xp -= amount;
    engine->trigger_event(engine, "xp_rem", this->xp, amount);
}