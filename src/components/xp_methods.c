/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** xp methods
*/

#include <components/health_component.h>
#include "components/xp_component.h"
#include "engine.h"

void level_up(gc_engine *engine)
{
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct health_component *health;

    if (!player)
        return;
    health = GETCMP(player, health_component);
    if (!health)
        return;
    health->health_max += 15;
    health->health = health->health_max;
}

void xp_add(struct xp_component *this, gc_engine *engine, \
unsigned int amount)
{
    if (this->full)
        return;
    this->xp += amount;
    if (this->xp >= 100) {
        this->full = true;
        this->xp = 100;
        level_up(engine);
    }
    engine->trigger_event(engine, "xp_add", this->xp, amount);
}

void xp_rem(struct xp_component *this, gc_engine *engine, \
unsigned int amount)
{
    this->xp -= amount;
    engine->trigger_event(engine, "xp_rem", this->xp, amount);
}