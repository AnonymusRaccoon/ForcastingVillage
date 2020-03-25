/*
** EPITECH PROJECT, 2019
** Sum stdarg
** File description:
** sum_stdarg
*/

#include "formaters.h"
#include "my.h"
#include <stdarg.h>
#include <unistd.h>

formater_t formaters[] = {{string_formater, 's'},
    {string_nonprintable_formater, 'S'},
    {char_formater, 'c'},
    {int_formater, 'i'},
    {int_formater, 'd'},
    {octal_formater, 'o'},
    {hexa_formater, 'x'},
    {big_hexa_formater, 'X'},
    {uint_formater, 'u'},
    {ptr_formater, 'p'},
    {ubinary_formater, 'b'},
    {float_formater, 'f'},
    {float_formater, 'F'},
    {no_format, '%'},
    {0, 0}
};

const char modifiersCst[] = "#0-+ hl";

int format(va_list ap, char flag, char modifiers[MODIFIERS_SIZE])
{
    for (int i = 0; formaters[i].flag; i++) {
        if (formaters[i].flag == flag) {
            return (formaters[i].func(ap, modifiers));
        }
    }
    return (0);
}

int is_flag(char c)
{
    for (int i = 0; formaters[i].flag; i++) {
        if (formaters[i].flag == c) {
            return (1);
        }
    }
    return (0);
}

int is_modifier(char c)
{
    for (int i = 0; modifiersCst[i]; i++) {
        if (modifiersCst[i] == c)
            return (1);
    }
    return (0);
}

int get_modifiers(const char *str, char flags[MODIFIERS_SIZE])
{
    int i;

    for (i = 0; !is_flag(str[i]); i++) {
        if (!is_modifier(str[i]) && !is_num(str[i]))
            return (-1);
        flags[i] = str[i];
    }
    flags[i] = '\0';
    return (i);
}

int my_printf(const char *str, ...)
{
    int count = 0;
    va_list ap;
    char modifiers[MODIFIERS_SIZE];
    int next_is_flag;

    va_start(ap, str);
    for (int i = 0; str[i]; i++) {
        if (str[i] == '%') {
            next_is_flag = 1;
            i++;
            i += get_modifiers(&str[i], modifiers);
        } else
            next_is_flag = 0;
        if (next_is_flag && is_flag(str[i]))
            count += format(ap, str[i], modifiers);
        else
            count += write(1, &str[i], 1);
    }
    va_end(ap);
    return (count);
}