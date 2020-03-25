//
// Created by anonymus-raccoon on 3/3/20.
//

#ifndef _TEAMS_COMPONENT_C_
#define _TEAMS_COMPONENT_H_

#include "component.h"

struct game_manager
{
    gc_component base;
    int happiness;
    int stupidity;
};

const struct game_manager game_manager;

#endif //_TEAMS_COMPONENT_C_
