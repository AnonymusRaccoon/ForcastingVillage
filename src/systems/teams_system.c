/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** teams_system
*/

#include "entity.h"
#include "system.h"
#include "prefab.h"
#include "components/teams_component.h"
#include <stddef.h>
#include <stdlib.h>
#include "components/tag_component.h"
#include "components/fixed_to_cam_component.h"
#include "components/game_manager.h"
#include "my.h"

void pm_destroy(gc_scene *scene, int prefab_id)
{
    for (gc_list *ent = scene->entities; ent; ent = ent->next)
        if (((gc_entity *)ent->data)->prefab_id == prefab_id)
            ((gc_entity *)ent->data)->destroy(ent->data, scene);
}

void pm_clicked(gc_engine *engine, gc_entity *entity)
{
    float y_pos = GETCMP(entity, fixed_to_cam)->pos.y;

    pm_destroy(engine->scene, entity->prefab_id);
    teams_move_up(engine->scene, -15, y_pos);
}

bool teams_move_up(gc_scene *scene, float amount, float y_level)
{
    gc_list *list = scene->get_entity_by_cmp(scene, "tag_component");
    struct fixed_to_cam *fc;
    struct tag_component *tc;
    int pm_to_destroy = -1;

    for (; list; list = list->next) {
        tc = GETCMP(list->data, tag_component);
        if (my_strcmp(tc->tag, "teams"))
            continue;
        fc = GETCMP(list->data, fixed_to_cam);
        if (!fc || fc->pos.y > y_level)
            continue;
        fc->pos.y -= amount;
        if (fc->pos.y < 15)
            pm_to_destroy = ((gc_entity *)list->data)->prefab_id;
    }
    if (pm_to_destroy != -1)
        pm_destroy(scene, pm_to_destroy);
    return (pm_to_destroy != -1);
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct teams_component *team = GETCMP(entity, teams_component);
    struct game_manager *manager = GETCMP(entity, game_manager);
    int index;

    if (!manager) {
        my_printf("No game manager found. Teams is disabled.\n");
        return;
    }
    if (engine->scene->is_paused)
        return;
    team->next_teams -= dtime;
    if (team->next_teams < 0 && team->prefab_count) {
        index = random() % team->prefab_count;
        team->next_teams = team->delay;
        if (teams_move_up(engine->scene, team->prefabs_size[index], 1000))
            manager->happiness -= 10;
        prefab_load(engine, team->prefabs[index]);
    }
}

static void destroy(void *system)
{
    (void)system;
}

const gc_system teams_system = {
    name: "teams_system",
    component_name: "teams_component",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &destroy
};