/*
** EPITECH PROJECT, 2019
** Memory dump
** File description:
** Debug Library
*/

const char *hex = "0123456789abcdef";

#include "my.h"
#include <unistd.h>

int get_size(long n, const char *base);

void my_putchar(char c);

int is_printable(char c);

void display_x_char(char c, int count)
{
    for (int i = 0; i < count; i++)
        write(1, &c, 1);
}

void print_ptr(void *ptr)
{
    write(1, "0x", 2);
    my_putlong_base((long)ptr, hex);
}

void print_hexa(char *ptr, int size)
{
    for (int i = 0; i < 16; i++) {
        if (i >= size) {
            display_x_char(' ', 40 - (i * 2 + i / 2));
            return;
        }
        if (ptr[i] < 16)
            my_putchar('0');
        my_putlong_base((long)ptr[i], hex);
        if (i % 2 == 1)
            my_putchar(' ');
    }
}

void print_str_to(char *ptr, int max)
{
    int overflow = 0;

    for (int i = 0; i < max; i++) {
        if (overflow || !is_printable(ptr[i]))
            my_putchar('.');
        else
            my_putchar(ptr[i]);
        if (!overflow)
            overflow = ptr[i] == '\0';
    }
}

void my_showmem(char *str, int size)
{
    int padding = size % 16;
    int line_count = padding == 0 ? size / 16 : size / 16 + 1;
    char *ptr;

    for (int i = 0; i < line_count; i++) {
        ptr = (str + i * 16);
        print_ptr((void *)(ptr - str));
        print_hexa(ptr, size - i * 16);
        print_str_to(ptr, 16);
        my_putchar('\n');
    }
}
