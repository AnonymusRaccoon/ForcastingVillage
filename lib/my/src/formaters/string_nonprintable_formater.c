/*
** EPITECH PROJECT, 2019
** String formater
** File description:
** string_formater
*/

#include <stdarg.h>
#include <unistd.h>
#include "formaters.h"
#include "my.h"

int string_nonprintable_formater(va_list ap, char mod[MODIFIERS_SIZE])
{
    char *var = va_arg(ap, char *);

    my_showstr(var);
    return (0);
}