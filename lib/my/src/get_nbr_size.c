/*
** EPITECH PROJECT, 2019
** Get nbr size
** File description:
** get_nbr_size
*/

#include "my.h"

int get_nbr_len(long long int n, const char *base)
{
    int base_size = my_strlen(base);
    int i = 1;

    if (n < 0) {
        n *= -1;
        i++;
    }
    while (n >= base_size) {
        n /= base_size;
        i++;
    }
    return (i);
}