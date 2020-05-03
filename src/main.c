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

int main(int argc, char **av)
{
    bool map_editor = false;

    if (argc != 1 && !my_strcmp(av[1], "-h"))
        return (usage(av[0]));
    if (argc > 1)
        map_editor = !my_strcmp(av[1], "-e") || !my_strcmp(av[1], "--editor");
    return (start_game(map_editor));
}