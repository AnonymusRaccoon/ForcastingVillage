/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** keyboard_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct keyboard_controller
{
    gc_component base;
    int left_key;
    int right_key;
    int up_key;
    int down_key;
};

extern const struct keyboard_controller keyboard_controller;