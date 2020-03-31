/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_movement_system.c
*/


#include <components/controllable_component.h>
#include <components/transform_component.h>
#include "map_utils.h"
#include "system.h"


static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct controllable_component *ctl = GETCMP(entity, controllable_component);
    struct transform_component *tra = GETCMP(entity, transform_component);
    gc_vector2 move = gc_vector2_from_coords(ctl->movement_x, ctl->movement_y, 0);
    struct vertex_component *map = GETSYS(engine, vertex_component);
    gc_vector2 new_pos = gc_vector2_add(tra->position, move);
    struct tile *new_tile = get_tile_from_pos(map, new_pos);

    if (new_tile && !new_tile->solid && ctl->move_callback <= 0) {
        tra->position.x += move.x;
        tra->position.y += move.y;
        ctl->move_callback = 10;
    }
    ctl->move_callback--;
}

static void ctr(void *system, va_list list)
{
}

static void destroy(void *system)
{
}

const gc_system map_movement_system = {
    name: "map_movement_system",
    component_name: "map_movement",
    size: sizeof(gc_system),
    ctr: ctr,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &destroy
};