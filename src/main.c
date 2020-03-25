/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** main
*/

#include "setup.h"
#include "my.h"

int usage(char *bin)
{
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 1 && !my_strcmp(argv[1], "-h"))
        return (usage(argv[0]));
    return (start_game());
}