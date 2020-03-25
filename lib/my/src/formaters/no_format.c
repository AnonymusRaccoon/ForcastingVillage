/*
** EPITECH PROJECT, 2019
** int formater
** File description:
** int_formater
*/

#include "formaters.h"
#include "my.h"
#include <stdarg.h>
#include <unistd.h>

int no_format(va_list _ap, char mod[MODIFIERS_SIZE])
{
    return (write(1, "%", 1));
}