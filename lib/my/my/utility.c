/*
** EPITECH PROJECT, 2019
** Utility for the showmem
** File description:
** utility
*/

#include "my.h"

int get_size(long n, const char *base)
{
    int base_size = my_strlen(base);
    int i = 1;

    while (n >= base_size) {
        n /= base_size;
        i++;
    }
    return (i);
}