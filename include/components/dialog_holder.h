/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_holder.h
*/

#ifndef MY_RPG_DIALOG_HOLDER_H
#define MY_RPG_DIALOG_HOLDER_H

#include "component.h"

struct dialog_input {
    char *text;
    void (*callback)(gc_engine *engine, int input_index);
};

struct dialog_line {
    char *name;
    char *text;
    int input_count;
    struct dialog_input *inputs;
};

struct dialog_holder {
    gc_component base;
    struct dialog_line **text;
    bool single_usage;
    bool has_seen;
    struct tile *tile;
};

const struct dialog_holder dialog_holder;

struct dialog_manager {
    gc_system base;
    int dialog_id;
    int input_id;
    int current_line;
    int input_index;
    struct dialog_line *current_text;
    struct dialog_holder *current_dialog;
    struct dialog_input *current_input;
};

const struct dialog_manager dialog_manager;

void dialog_next(gc_engine *engine);
void dialog_add_line(struct dialog_holder *this, char *name, char *text, \
struct dialog_input *inputs);

#endif //MY_RPG_DIALOG_HOLDER_H
