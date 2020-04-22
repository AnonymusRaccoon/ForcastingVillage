/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** player.c
*/

#include "engine.h"
#include "components/attack_component.h"

static void ctr(void *component, va_list args)
{
    struct attack_component *cmp = (struct attack_component *)component;

    cmp->attacks = va_arg(args, gc_data *);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct attack_component *cmp = (struct attack_component *)component;

    // SET ATTACKS FROM the xml.
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

const struct attack_component attack_component = {
    base: {
        name: "attack_component",
        size: sizeof(struct attack_component),
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
