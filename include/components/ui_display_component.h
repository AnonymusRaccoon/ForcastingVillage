/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** ui display component
*/

#ifndef MY_RPG_UI_DISPLAY_COMPONENT_H
#define MY_RPG_UI_DISPLAY_COMPONENT_H

#include <stdbool.h>
#include "component.h"

struct ui_display_component
{
    gc_component base;
    bool display_health;
    bool display_xp;
};

extern const struct ui_display_component ui_display_component;

#endif //MY_RPG_UI_DISPLAY_COMPONENT_H
