/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_utility.c
*/

#include <stdlib.h>
#include "engine.h"
#include "prefab.h"
#include "enemy.h"
#include "my.h"
#include "systems/combat_manager.h"

void combat_create_enemy(struct combat_manager *this, gc_engine *engine, \
char *enemy_name)
{
    gc_list *li = this->game_scene->get_data(this->game_scene, "enemies", NULL);
    struct enemy *enemy = NULL;

    for (; li; li = li->next) {
        enemy = li->data;
        if ((!enemy_name && random() % 100 < enemy->spawn_rate)
            || (enemy_name && !my_strcmp(enemy_name, enemy->name)))
            break;
    }
    if ((this->current_enemy = enemy))
        prefab_load(engine, enemy->prefab_src);
}

bool get_player_and_enemy(gc_scene *sce, gc_entity **player, gc_entity **enemy)
{
    gc_list *enemies = sce->get_entity_by_cmp(sce, "attack_component");

    if (enemies && enemies->next && ((gc_entity *)enemies->data)->id == 50) {
        *player = enemies->data;
        *enemy = enemies->next->data;
    } else if (enemies && enemies->next) {
        *enemy = enemies->data;
        *player = enemies->next->data;
    }
    if (!*enemy || !*player)
        return (false);
    return (true);
}