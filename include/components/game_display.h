//
// Created by anonymus-raccoon on 3/3/20.
//

#ifndef _TEAMS_COMPONENT_C_
#define _TEAMS_COMPONENT_H_

#include "component.h"

typedef enum display_type
{
    SELECT_TILE_DISPLAY,
    xp_display
} display_type_enum;

struct game_display
{
    gc_component base;
    display_type_enum type;
};

const struct game_display game_display;
const struct gc_system game_display_system;

#endif //_TEAMS_COMPONENT_C_
