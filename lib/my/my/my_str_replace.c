/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** my_str_replace
*/

#include "my.h"

char *my_str_replace(char *str, const char *to_replace, char c)
{
    char *p;
    int len = my_strlen(to_replace);

    while ((p = my_strstr(str, to_replace))) {
        *p = c;
        p++;
        for (char *ptr = p + len - 1; *ptr; ptr++, p++)
            *p = *ptr;
        *p = '\0';
    }
    return (str);
}