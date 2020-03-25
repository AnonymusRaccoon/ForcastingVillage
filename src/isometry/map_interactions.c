/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_interactions
*/

#include "map_interactions.h"
#include "components/clickable_component.h"
#include "entity.h"
#include "my.h"
#include <math.h>
#include "components/transform_component.h"
#include "map_utils.h"
#include <stdlib.h>
#include "components/isometry/map_manager_component.h"

void click_tile(gc_engine *engine, struct map_manager_component *manager, \
struct tile *ret, bool is_left)
{
    bool r = manager->brush == RESET;

    switch (manager->brush) {
    case ROTATE:
        ret->data = (ret->data + (is_left ? 1 : -1U)) % 4;
        break;
    case TEXTURE:
        ret->texture = manager->selected_texture;
        break;
    case MOVE:
    case RESET:
        move_verticies(engine, ret, ALL_VERTICES | is_left, r);
        break;
    }
}

bool map_onclick(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
    struct vertex_component *map = GETCMP(entity, vertex_component);
    struct map_manager_component *m = GETCMP(entity, map_manager_component);
    struct transform_component *tc = GETCMP(entity, transform_component);
    struct tile *t = get_tile_from_pos(map, gc_vector2_add(pos, tc->position));
    bool r;
    int ind;

    if (!map || !m) {
        my_printf("map not found\n");
        return (false);
    }
    r = m->brush == RESET;
    if (!t)
        return (false);
    if (m->tile_mode)
        click_tile(engine, m, t, key == GC_LEFT);
    else {
        ind = get_index_nearest_vertex(t, gc_vector2_add(pos, tc->position));
        move_verticies(engine, t, (int)pow(2, ind + 1) | (key == GC_LEFT), r);
    }
    return (false);
}

void move_verticies(gc_engine *engine, struct tile *ret, char mode, bool r)
{
    int val = (mode & INVERT_ADD_VALUE) ? ADD_VALUE : -ADD_VALUE;

    for (int i = 0; i < 4; i++) {
        if (mode & (int)pow(2, i + 1))
            ret->corners[i]->z += (r) ? -ret->corners[i]->z : val;
    }
}