/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** player.c
*/

#include "engine.h"
#include "components/player_component.h"

static void ctr(void *component, va_list args)
{
    struct player_component *cmp = (struct player_component *)component;

    cmp->fight_rate = va_arg(args, int);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct player_component *cmp = (struct player_component *)component;

    cmp->fight_rate = xml_getintprop(n, "fight_rate");
}

static void dtr(void *component)
{
    (void)component;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct player_component player_component = {
    base: {
        name: "player_component",
        size: sizeof(struct player_component),
        dependencies: (char *[]) {
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};
