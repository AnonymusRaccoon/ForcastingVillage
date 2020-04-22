/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_methods.c
*/

#include <stdlib.h>
#include "systems/combat_manager.h"
#include "tile.h"
#include "components/player_component.h"
#include "prefab.h"
#include "components/attack_component.h"
#include "engine.h"
#include "my.h"
#include "components/dialog_holder.h"
#include "components/combat_holder.h"
#include "enemy.h"

void combat_start(gc_engine *engine, char *enemy_name)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    gc_list *li = engine->scene->get_data(engine->scene, "enemies", NULL);
    gc_scene *scene = scene_create(engine, "prefabs/combat.gcprefab");
    struct enemy *enemy = NULL;

    if (!scene) {
        my_printf("The combat scene couldn't be found.\n");
        return;
    }
    this->game_scene = engine->scene;
    engine->scene = NULL;
    engine->change_scene(engine, scene);
    dialog_next(engine);
    for (; li; li = li->next) {
        enemy = li->data;
        if ((!enemy_name && random() % 100 < enemy->spawn_rate)
            || (enemy_name && !my_strcmp(enemy_name, enemy->name)))
            break;
    }
    if ((this->current_enemy = enemy))
        prefab_load(engine, enemy->prefab_src);
}

void attack_callback(gc_engine *engine, int index)
{
    printf("Launching attack %d\n", index);
}

void show_attacks(struct combat_holder *cmp, struct dialog_holder *dialog, \
gc_scene *scene)
{
    gc_entity *player_entity = scene->get_entity(scene, 50);
    struct attack_component *player;
    static struct dialog_input inputs[5];
    int i = 0;

    if (!player_entity)
        return;
    player = GETCMP(player_entity, attack_component);
    if (!player)
        return;
    if (player->attacks) {
        for (i = 0; player->attacks[i].name && i < 4; i++) {
            inputs[i].text = player->attacks[i].name;
            inputs[i].callback = &attack_callback;
        }
    }
    inputs[i].text = NULL;
    dialog_add_line(dialog, NULL, ATTACK_TEXT, inputs);
    cmp->state = ATTACKING;
}