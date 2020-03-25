//
// Created by anonymus-raccoon on 3/10/20.
//

#ifndef _MAP_MANAGER_COMPONENT_H_
#define _MAP_MANAGER_COMPONENT_H_

#include "component.h"

enum brush
{
    MOVE,
    RESET,
    ROTATE,
    TEXTURE
};

struct map_manager_component
{
    gc_component base;
    bool tile_mode;
    enum brush brush;
    void *selected_texture;
};

const struct map_manager_component map_manager_component;

#endif //_MAP_MANAGER_COMPONENT_H_
