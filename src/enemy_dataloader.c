/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** enemies_dataloader.c
*/

#include "engine.h"
#include <malloc.h>
#include <my.h>
#include "enemy.h"

static void free_enemy(gc_list *list)
{
    struct enemy *data;

    if (!list)
        return;
    free_enemy(list->next);
    data = (struct enemy *)list->data;
    free(data->name);
    free(data->prefab_src);
}

static void free_enemies(gc_data *data)
{
    free_enemy(data->custom);
}

gc_data *enemies_dataloader(gc_engine *engine, gc_scene *scene, node *n)
{
    gc_data *data = malloc(sizeof(*data));
    struct enemy *enemy;

    if (!data)
        return (NULL);
    data->type = my_strdup("enemies");
    data->name = NULL;
    data->destroy = &free_enemies;
    data->custom = NULL;
    for (n = n->child; n; n = n->next) {
        enemy = malloc(sizeof(*enemy));
        if (!enemy)
            return (NULL);
        enemy->name = xml_getproperty(n, "name");
        enemy->prefab_src = xml_getproperty(n, "src");
        enemy->spawn_rate = xml_getintprop(n, "spawn_rate");
        LISTADD(data->custom, enemy);
    }
    return (data);
}