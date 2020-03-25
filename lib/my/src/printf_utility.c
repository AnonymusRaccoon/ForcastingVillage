/*
** EPITECH PROJECT, 2019
** Utility for the flags
** File description:
** utility
*/

#include "formaters.h"

int count(char c, char *str)
{
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            count++;
    }
    return (count);
}

int contains(char c, char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            return (1);
    }
    return (0);
}

int last_mod(char *modifiers)
{
    for (int i = 0; modifiers[i]; i++) {
        if (!is_modifier(modifiers[i]))
            return (i);
    }
    return (0);
}