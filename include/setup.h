/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** runner
*/

#pragma once

#define ERROR 84
#include "scene.h"

int start_game(bool map_editor);

bool start_button(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool options(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool goto_main_menu(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool quit(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool catch(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool toggle_pause(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool toggle_inventory(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);

int checkbox_update(gc_scene *s, gc_entity *entity, bool checked);
void resolution_set_txt(gc_entity *entity, gc_engine *engine, \
enum gc_mousekeys __);
void framerate_set_text(gc_entity *entity, gc_engine *engine, \
enum gc_mousekeys __);

bool fullscreen(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool resolution_down(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool resolution_up(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool framerate_up(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);
bool framerate_down(gc_engine *engine, gc_entity *entity, gc_vector2 _, \
enum gc_mousekeys __);

bool dialog_input0(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);
bool dialog_input1(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);
bool dialog_input2(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);
bool dialog_input3(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);

gc_data *enemies_dataloader(gc_engine *engine, gc_scene *scene, node *n);

void fireball(gc_engine *engine, gc_entity *from, gc_entity *enemy);
void uppercut(gc_engine *engine, gc_entity *from, gc_entity *enemy);
void water_jet(gc_engine *engine, gc_entity *from, gc_entity *enemy);
void shield(gc_engine *engine, gc_entity *from, gc_entity *enemy);

void load_attacks(gc_scene *scene);