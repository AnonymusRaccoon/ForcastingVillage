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

int float_formater(va_list ap, char mod[MODIFIERS_SIZE])
{
    double var = va_arg(ap, double);
    int decimal = (var - (int)var) * 1000000 + 1;

    while (decimal % 10 == 0)
        decimal /= 10;
    my_put_nbr((int)var);
    write(1, ".", 1);
    my_put_nbr(decimal);
    return (0);
}