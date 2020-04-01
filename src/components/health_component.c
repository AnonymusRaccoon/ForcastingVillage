/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** health component
*/

#include "xml.h"
#include "component.h"
#include "components/health_component.h"

static void health_ctr(void *component, va_list args)
{
    struct controllable_component *cmp = (struct controllable_component *)\
component;

    (void)args;
}

static void health_fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
    struct controllable_component *cmp = (struct controllable_component *)\
component;

    (void)scene;
    (void)entity;
    (void)n;
}

static void health_dtr(void *component)
{
    (void)component;
}

static char *health_serialize(void *component)
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
                ctr: &health_ctr,
                fdctr: &health_fdctr,
                dtr: &health_dtr,
                serialize: &health_serialize,
                destroy: &component_destroy
        }
};