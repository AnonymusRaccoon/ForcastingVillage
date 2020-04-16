/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_input.c
*/

#include <components/dialog_holder.h>
#include "engine.h"

bool dialog_input0(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
    struct dialog_manager *man = GETSYS(engine, dialog_manager);

    man->current_input = &man->current_text->inputs[0];
    dialog_next(engine);
    if (man->current_input->callback)
        man->current_input->callback(engine, entity, pos, key);
    return (true);
}

bool dialog_input1(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
    struct dialog_manager *man = GETSYS(engine, dialog_manager);

    man->current_input = &man->current_text->inputs[1];
    dialog_next(engine);
    if (man->current_input->callback)
        man->current_input->callback(engine, entity, pos, key);
    return (true);
}

bool dialog_input2(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
    struct dialog_manager *man = GETSYS(engine, dialog_manager);

    man->current_input = &man->current_text->inputs[2];
    dialog_next(engine);
    if (man->current_input->callback)
        man->current_input->callback(engine, entity, pos, key);
    return (true);
}

bool dialog_input3(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
    struct dialog_manager *man = GETSYS(engine, dialog_manager);

    man->current_input = &man->current_text->inputs[3];
    dialog_next(engine);
    if (man->current_input->callback)
        man->current_input->callback(engine, entity, pos, key);
    return (true);
}