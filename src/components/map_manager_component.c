/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** map_manager_component
*/

#include <components/isometry/map_manager_component.h>
#include "engine.h"
#include "entity.h"
#include "xml.h"
#include "my.h"


static void ctr(void *comp, va_list args)
{
    struct map_manager_component *cmp = (struct map_manager_component *)comp;

    cmp->tile_mode = true;
    cmp->brush = MOVE;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *comp, node *n)
{
    struct map_manager_component *cmp = (struct map_manager_component *)comp;
    void **data = scene->get_data(scene, "tiles", NULL);

    cmp->tile_mode = true;
    cmp->brush = MOVE;
    if (data)
        cmp->selected_texture = data[0];
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

const struct map_manager_component map_manager_component = {
    base: {
        name: "map_manager_component",
        size: sizeof(struct map_manager_component),
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