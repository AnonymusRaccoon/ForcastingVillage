/*
** EPITECH PROJECT, 2019
** Put nbr in a custom base
** File description:
** Might be useful later
*/

#include <unistd.h>
#include "formaters.h"

int my_strlen(const char *str);

static void display_a_digit(char c)
{
    write(1, &c, 1);
}

static void put_digit(long long int n, int base_length, const char *base)
{
    if (n > base_length - 1)
        put_digit(n / base_length, base_length, base);
    display_a_digit(base[n % base_length]);
}

int my_putlonglong_base(long long int nbr, const char *base, int nbrlen)
{
    int base_length = my_strlen(base);

    if (base_length < 2) {
        display_a_digit(base[0]);
        return (0);
    }
    if (nbr < 0) {
        nbr *= -1;
        display_a_digit('-');
        nbrlen--;
    }
    for (int i = get_nbr_len(nbr, base); i < nbrlen; i++)
        write(1, base, 1);
    put_digit(nbr, base_length, base);
    return (nbrlen + nbr < 0 ? 1 : 0);
}
