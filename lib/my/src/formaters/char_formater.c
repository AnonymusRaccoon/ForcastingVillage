/*
** EPITECH PROJECT, 2019
** Char formater
** File description:
** char_formater
*/

#include "formaters.h"
#include "my.h"
#include <stdarg.h>
#include <unistd.h>

int char_formater(va_list ap, char mod[MODIFIERS_SIZE])
{
    char var = (char)va_arg(ap, int);

    return (write(1, &var, 1));
}