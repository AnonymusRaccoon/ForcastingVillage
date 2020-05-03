/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_methods.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "components/renderer.h"
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
    gc_scene *scene = scene_create(engine, "prefabs/combat.gcprefab");
    gc_entity *player;
    gc_entity *player_combat;

    if (!scene) {
        my_printf("The combat scene couldn't be found.\n");
        return;
    }
    player = engine->scene->get_entity(engine->scene, 50);
	player_combat = scene->get_entity(scene, 50);
    this->state = ATTACK;
    this->game_scene = engine->scene;
    set_combat_player(engine, player, player_combat);
    engine->scene = NULL;
    engine->change_scene(engine, scene);
    load_attacks(scene);
    dialog_next(engine);
    combat_create_enemy(this, engine, enemy_name);
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
    if (!(player = GETCMP(player_entity, attack_component)))
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
    if (GETCMP(player_entity, health_component)->dead) {
        combat_end(engine, false);
        return;
    }
    if (!(player = GETCMP(player_entity, attack_component)))
        return;
    if (player->attacks)
        for (i = 0; player->attacks[i].name && i < 4; i++) {
            inputs[i].text = player->attacks[i].name;
            inputs[i].callback = &attack_callback;
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
    struct renderer *rend;

    if (!get_player_and_enemy(engine->scene, &player, &enemy))
        return;
    rend = GETCMP(player, renderer);
    if (rend)
        rend_set_anim(rend, "none");
    if (GETCMP(enemy, health_component)->dead)
        combat_end(engine, true);
    else if (this->next_enemy_attack->run)
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

    if (!get_player_and_enemy(scene, &player, &enemy)
        ||!(enemy_attack = GETCMP(enemy, attack_component)))
        return;
    for (count = 0; enemy_attack->attacks[count].name; count++);
    if (count == 0) {
        my_printf("No attack found for the enemy.\n");
        return;
    }
    this->next_enemy_attack = &enemy_attack->attacks[random() % count];
    snprintf(str, 150, "%s uses %s.", enemy_attack->name, \
this->next_enemy_attack->name);
    if ((line = dialog_add_line(dialog, NULL, str, NULL)))
        line->callback = &defend_callback;
    this->state = DEFENDING;
}