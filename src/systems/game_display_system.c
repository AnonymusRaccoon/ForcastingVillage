/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** teams_system
*/

#include "entity.h"
#include "system.h"
#include <stddef.h>
#include "components/game_display.h"
#include "components/game_manager.h"
#include "components/xp_component.h"
#include "map_editor.h"
#include "text.h"
#include "components/renderer.h"
#include <malloc.h>
#include "sprite.h"

void display_current_texture(gc_scene *scene, struct renderer *rend)
{
    gc_list *li = scene->get_entity_by_cmp(scene, "map_manager_component");
    struct map_manager_component *map;

    if (!li)
        return;
    map = GETCMP(li->data, map_manager_component);
    ((gc_sprite *)rend->data)->texture = map->selected_texture;
}

void display_current_xp(gc_scene *scene, struct renderer *rend)
{
    gc_entity *player = scene->get_entity(scene, 50);
    struct xp_component *xp;
    static char str[10];

    if (!player)
        return;
    xp = GETCMP(player, xp_component);
    if (!xp)
        return;
    snprintf(str, 10, "%d/100", xp->xp);
    ((gc_text *)rend->data)->text = str;
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct game_display *disp = GETCMP(entity, game_display);
    struct renderer *rend = GETCMP(entity, renderer);
    gc_scene *scene = engine->scene;

    if (disp->type == SELECT_TILE_DISPLAY && rend->type == GC_TEXTUREREND){
        display_current_texture(scene, rend);
        return;
    }
    if (disp->type == XP_DISPLAY && rend->type == GC_TXTREND) {
        display_current_xp(scene, rend);
        return;
    }
}

static void destroy(void *system, gc_engine *engine)
{
    (void)system;
}

const gc_system game_display_system = {
    name: "game_display_system",
    component_name: "game_display",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &destroy
};