/*
** EPITECH PROJECT, 2019
** Formater struct
** File description:
** formaters
*/

#pragma once
#include <stdarg.h>

#define MODIFIERS_SIZE 50

typedef struct formater
{
    int (*func)(va_list ap, char modifiers[MODIFIERS_SIZE]);
    char flag;
} formater_t;

int string_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int string_nonprintable_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int char_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int int_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int uint_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int ptr_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int ubinary_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int octal_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int hexa_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int big_hexa_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int float_formater(va_list ap, char modifiers[MODIFIERS_SIZE]);
int no_format(va_list ap, char modifiers[MODIFIERS_SIZE]);

int count(char c, char *str);
int contains(char c, char *str);
int get_nbr_len(long long int n, const char *base);
int is_modifier(char c);
int last_mod(char *modifiers);
int my_putlonglong_base(long long int nbr, const char *base, int length);