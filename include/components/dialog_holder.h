/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_holder.h
*/

#ifndef MY_RPG_DIALOG_HOLDER_H
#define MY_RPG_DIALOG_HOLDER_H

#include "component.h"

struct dialog_holder {
    gc_component base;
    char **text;
    bool single_usage;
    bool has_seen;

    int current_line;
    char *current_text;
};

const struct dialog_holder dialog_holder;

#endif //MY_RPG_DIALOG_HOLDER_H
