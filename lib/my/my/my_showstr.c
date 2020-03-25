/*
** EPITECH PROJECT, 2019
** Show Str With non printable values in hexa
** File description:
** Debugger Library
*/

#include <unistd.h>

int is_printable(char c);

int my_putnbr_base(int i, const char *base);

void puthex(char c)
{
    write(1, "\\", 1);
    if (c < 8)
        write(1, "0", 1);
    if (c < 16)
        write(1, "0", 1);
    my_putnbr_base(c, "01234567");
}

int my_showstr(const char *str)
{
    for (int i = 0; str[i]; i++) {
        if (is_printable(str[i]))
            write(1, &(str[i]), 1);
        else
            puthex(str[i]);
    }
    return (0);
}
