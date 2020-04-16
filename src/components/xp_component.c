/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** xp component
*/

#include "xml.h"
#include "component.h"
#include "components/xp_component.h"

static void ctr(void *component, va_list args)
{
    struct xp_component *cmp = (struct xp_component *)\
component;
    cmp->xp = va_arg(args, int);
    cmp->full = false;
}

static void fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
    struct xp_component *cmp = (struct xp_component *)\
component;

    cmp->xp = xml_getintprop(n, "xp");
    cmp->full = false;
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

const struct xp_component xp_component = {
    base: {
        name: "xp_component",
        size: sizeof(struct xp_component),
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