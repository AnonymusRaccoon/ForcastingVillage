/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** player.c
*/

#include "engine.h"
#include "components/attack_component.h"
#include <malloc.h>

static void ctr(void *component, va_list args)
{
    struct attack_component *cmp = (struct attack_component *)component;

    cmp->attacks = va_arg(args, attack_holder *);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct attack_component *cmp = (struct attack_component *)component;
    int i = 0;
    char *name;

    cmp->attacks = malloc(sizeof(attack_holder) * xml_getchildcount(n));
    if (!cmp->attacks)
        return;
    for (n = n->child; n; n = n->next) {
        name = xml_getproperty(n, "name");
        cmp->attacks[i].name = name;
        cmp->attacks[i].run = scene->get_data(scene, "attack", name);
        i++;
    }
    cmp->attacks[i].name = NULL;
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
