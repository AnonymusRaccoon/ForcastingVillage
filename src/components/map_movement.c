/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_movement.c
*/


#include "components/map_movement.h"
#include "xml.h"
#include "component.h"

static void ctr(void *component, va_list args)
{
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{

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

const struct map_movement map_movement = {
    base: {
        name: "map_movement",
        size: sizeof(struct map_movement),
        dependencies: (char *[]) {
            "controllable_component",
            "transform_component",
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};