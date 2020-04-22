/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_holder.c
*/

#include "engine.h"
#include "components/combat_holder.h"

static void ctr(void *component, va_list args)
{
    struct combat_holder *cmp = component;

    cmp->state = ATTACK;
    cmp->name = va_arg(args, char *);
}

static void fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
    struct combat_holder *cmp = component;

    cmp->name = xml_getproperty(n, "name");
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

const struct combat_holder combat_holder = {
    base: {
        name: "combat_holder",
        size: sizeof(struct combat_holder),
        dependencies: (char *[]){
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};