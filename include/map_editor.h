/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_editor.h
*/


#ifndef MY_RPG_MAP_EDITOR_H
#define MY_RPG_MAP_EDITOR_H

#include "engine.h"
#include "components/vertex_component.h"
#include "keybindings.h"
#include "component.h"
#include <stdbool.h>

enum modes_on_tile {
    VERTEX_0 = 2,
    VERTEX_1 = 4,
    VERTEX_2 = 8,
    VERTEX_3 = 16,
    ALL_VERTICES = 30,
    INVERT_ADD_VALUE = 1
};

bool map_onclick(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);
bool tile_select(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);
bool vertex_select(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);
bool up_down(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);
bool reset(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);
bool rotate(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);
bool texture(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);
bool switch_texture(gc_engine *engine, gc_entity *entity, gc_vector2 _,
enum gc_mousekeys __);

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

#define ADD_VALUE 10

void move_verticies(gc_engine *engine, struct tile *ret, char mode, bool r);
int get_index_nearest_vertex(struct tile *sel, gc_vector2 pos);
struct tile *get_tile_from_pos(struct vertex_component *map, gc_vector2 pos);
bool map_manage_click(gc_engine *engine, int id, gc_vector2 pos);
gc_vector2 gc_vector2_from_coords(float x, float y, float z);
bool is_pos_in_tile(gc_vector2 pos, struct tile *tile);

#endif //MY_RPG_MAP_EDITOR_H
