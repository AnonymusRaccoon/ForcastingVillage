/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_methods.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "systems/combat_manager.h"
#include "tile.h"
#include "prefab.h"
#include "components/attack_component.h"
#include "engine.h"
#include "my.h"
#include "components/dialog_holder.h"
#include "components/health_component.h"
#include "enemy.h"
#include "setup.h"
#include "player_utilities.h"

void combat_start(gc_engine *engine, char *enemy_name)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    gc_list *li = engine->scene->get_data(engine->scene, "enemies", NULL);
    gc_scene *scene = scene_create(engine, "prefabs/combat.gcprefab");
    struct enemy *enemy = NULL;
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    gc_entity *player_combat = scene->get_entity(scene, 50);

    if (!scene) {
        my_printf("The combat scene couldn't be found.\n");
        return;
    }
    this->game_scene = engine->scene;
    set_combat_player(player, player_combat);
    engine->scene = NULL;
    engine->change_scene(engine, scene);
    load_attacks(scene);
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
    if (!enemy || !player)
        return (false);
    return (true);
}

void attack_callback(gc_engine *engine, int index)
{
    gc_scene *scene = engine->scene;
    gc_list *li = scene->get_entity_by_cmp(scene, "dialog_holder");
    struct combat_manager *this = GETSYS(engine, combat_manager);
    struct dialog_holder *dialog;
    static char str[150];
    gc_entity *player_entity = NULL;
    gc_entity *enemy = NULL;
    struct attack_component *player;

    if (!li || !get_player_and_enemy(scene, &player_entity, &enemy))
        return;
    player = GETCMP(player_entity, attack_component);
    if (!player)
        return;
    if (player->attacks[index].run)
        player->attacks[index].run(engine, player_entity, enemy);
    dialog = GETCMP(li->data, dialog_holder);
    snprintf(str, 150, "You used %s.", player->attacks[index].name);
    dialog_add_line(dialog, NULL, str, NULL);
    this->state = DEFEND;
}

void show_attacks(struct combat_manager *this, struct dialog_holder *dialog, \
gc_scene *scene, gc_engine *engine)
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
    this->state = ATTACKING;
}

void defend_callback(gc_engine *engine)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    gc_entity *player = NULL;
    gc_entity *enemy = NULL;

    if (!get_player_and_enemy(engine->scene, &player, &enemy))
        return;
    if (this->next_enemy_attack->run)
        this->next_enemy_attack->run(engine, enemy, player);
    this->state = ATTACK;
}

void defend(struct combat_manager *this, struct dialog_holder *dialog, \
gc_scene *scene, gc_engine *engine)
{
    gc_entity *player = NULL;
    gc_entity *enemy = NULL;
    struct attack_component *enemy_attack;
    static char str[150];
    int count;
    struct dialog_line *line;

    if (!get_player_and_enemy(scene, &player, &enemy))
        return;
    if (!(enemy_attack = GETCMP(enemy, attack_component)))
        return;
    for (count = 0; enemy_attack->attacks[count].name; count++);
    if (count == 0) {
        my_printf("No attack found for the enemy.\n");
        return;
    }
    this->next_enemy_attack = &enemy_attack->attacks[random() % count];
    snprintf(str, 150, "%s uses attack %s.", "The bee", \
this->next_enemy_attack->name);
    if ((line = dialog_add_line(dialog, NULL, str, NULL)))
        line->callback = &defend_callback;
    this->state = DEFENDING;
}