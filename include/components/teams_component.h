//
// Created by anonymus-raccoon on 3/3/20.
//

#ifndef _TEAMS_COMPONENT_C_
#define _TEAMS_COMPONENT_H_

#include "component.h"

struct teams_component
{
    gc_component base;
    float next_teams;
    float delay;
    char **prefabs;
    int *prefabs_size;
    int prefab_count;
};

const struct teams_component teams_component;

bool teams_move_up(gc_scene *scene, float amount, float y_level);
void pm_clicked(gc_engine *engine, gc_entity *entity);

#endif //_TEAMS_COMPONENT_C_
