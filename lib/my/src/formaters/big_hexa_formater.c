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

int big_hexa_formater(va_list ap, char mod[MODIFIERS_SIZE])
{
    long long int var;
    int nbrlen;

    if (count('l', mod) >= 2)
        var = va_arg(ap, unsigned long long int);
    else if (count('l', mod) == 1)
        var = va_arg(ap, unsigned long);
    else
        var = va_arg(ap, unsigned int);
    if (contains('0', mod))
        nbrlen = my_getnbr(&mod[last_mod(mod)]);
    else
        nbrlen = 0;
    if (var != 0 && contains('#', mod))
        nbrlen -= write(1, "0X", 2);
    return (my_putlonglong_base(var, "0123456789ABCDEF", nbrlen));
}