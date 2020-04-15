/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_holder.h
*/

#ifndef MY_RPG_DIALOG_HOLDER_H
#define MY_RPG_DIALOG_HOLDER_H

#include "component.h"

struct dialog_line {
    char *name;
    char *text;
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
    int current_line;
    struct dialog_line *current_text;
    struct dialog_holder *current_dialog;
};

const struct dialog_manager dialog_manager;

#endif //MY_RPG_DIALOG_HOLDER_H
