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

int string_formater(va_list ap, char mod[MODIFIERS_SIZE])
{
    char *var = va_arg(ap, char *);
    int length;

    if (var == NULL) {
        write(1, "(null)", 7);
        return 7;
    }
    if (contains('0', mod))
        length = my_getnbr(&mod[last_mod(mod)]);
    else
        length = my_strlen(var);
    return (write(1, var, length));
}