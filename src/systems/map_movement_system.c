/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_movement_system.c
*/


#include "components/controllable_component.h"
#include "components/map_linker.h"
#include "map_utils.h"
#include "system.h"
#include <math.h>
#include <utility.h>
#include <components/renderer.h>
#include <stddef.h>
#include <components/transform_component.h>

static gc_vector2i get_new_map_pos(struct map_linker *link, \
struct controllable_component *ctl)
{
    if (!link->tile)
        return ((gc_vector2i){0, 0});
    gc_vector2i moves = (gc_vector2i){0, 0};

    link->offset = gc_vector2i_add(link->offset, (gc_vector2i){
        round(cos(-45) * -ctl->movement_x - sin(-45) * -ctl->movement_y),
        round(sin(-45) * -ctl->movement_x + cos(-45) * -ctl->movement_y)
    });
    moves.x = (link->offset.x / 9) % 9;
    moves.y = -(link->offset.y / 9) % 9;
//    if (moves.x != 0 || moves.y != 0)
//        printf("Moves: %d, %d, Offsets: %d, %d\n", moves[0], moves[1], link->offset.x, link->offset.y);
    if (link->offset.x > 8)
        link->offset.x = -8;
    if (link->offset.x < -8)
        link->offset.x = 8;
    if (link->offset.y > 8)
        link->offset.y = -8;
    if (link->offset.y < -8)
        link->offset.y = 8;
    return (gc_vector2i_add((gc_vector2i){
        link->tile->corners[0]->x, link->tile->corners[0]->y}, (gc_vector2i){moves.y, -moves.x}));
}

void set_animation(gc_entity *entity, struct controllable_component *ctl)
{
    char *w_ams[8] = {"walk_down", "walk_up", "walk_up_left", "walk_up_right", \
"walk_right", "walk_down_left", "walk_down_right", "walk_left"};
    struct renderer *renderer = GETCMP(entity, renderer);
    int ind = 0;
    char *anim;

    if (!renderer)
        return;
    if (!ctl->movement_x && !ctl->movement_y) {
        rend_set_anim(renderer, "none");
        return;
    }
    anim = (ctl->movement_y > 0) ? w_ams[1] : w_ams[0];
    if (ctl->movement_x) {
        ind = (ctl->movement_x >= 0) ? 1 : 0;
        if (!ctl->movement_y)
            anim = (ctl->movement_x > 0) ? w_ams[4] : w_ams[7];
        else
            anim = (ctl->movement_y > 0) ? w_ams[ind + 2] : w_ams[ind + 5];
    }
    rend_set_anim(renderer, anim);
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct controllable_component *ctl = GETCMP(entity, controllable_component);
    struct map_linker *link = GETCMP(entity, map_linker);
    gc_vector2i map_pos = get_new_map_pos(link, ctl);
    gc_scene *scene = engine->scene;
    gc_list *maps = scene->get_entity_by_cmp(scene, "vertex_component");
    struct vertex_component *map;
    struct tile *new_tile;

    if (!maps || !ctl->can_move)
        return;
    set_animation(entity, ctl);
    map = GETCMP(maps->data, vertex_component);
    new_tile = get_tile_at(map, map_pos);
    if (new_tile && !new_tile->solid && new_tile != link->tile) { //CHECK FOR OVERFLOW
        link->tile->entity = NULL;
        new_tile->entity = entity;
        engine->trigger_event(engine, "entity_moved", entity, link->tile);
    }
}

static void ctr(void *system, va_list list)
{
}

static void destroy(void *system, gc_engine *engine)
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