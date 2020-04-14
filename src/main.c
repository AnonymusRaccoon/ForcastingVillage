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
    bool map_editor = false;

    if (argc != 1 && !my_strcmp(argv[1], "-h"))
        return (usage(argv[0]));
    if (argc > 1 && (!my_strcmp(argv[1], "-e") || !my_strcmp(argv[1], "--editor")))
        map_editor = true;
    return (start_game(map_editor));
}