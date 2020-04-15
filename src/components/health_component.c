/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** health component
*/

#include "xml.h"
#include "component.h"
#include "components/health_component.h"

static void ctr(void *component, va_list args)
{
    struct health_component *cmp = (struct health_component *)\
component;
    cmp->health = va_arg(args, int);
    cmp->dead = false;
}

static void fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
    struct health_component *cmp = (struct health_component *)\
component;

    cmp->health = xml_getintprop(n, "health");
    cmp->dead = false;
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

const struct health_component health_component = {
    base: {
        name: "health_component",
        size: sizeof(struct health_component),
        dependencies: (char *[]){
                "event_component",
                NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};