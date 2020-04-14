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

void print_ptr(void *var);

int ptr_formater(va_list ap, char mod[MODIFIERS_SIZE])
{
    void *var = va_arg(ap, void *);

    print_ptr(var);
    return (0);
}