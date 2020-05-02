/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** boss.c
*/

#include <components/player_component.h>
#include <systems/combat_manager.h>
#include "engine.h"
#include "prefab.h"
#include "components/dialog_holder.h"
#include "my.h"

void spawn_boss(gc_engine *engine)
{
    struct dialog_holder *dialog = dialog_get_current(engine);

    if (prefab_load(engine, "prefabs/boss.gcprefab") < 0) {
        my_printf("Couldn't load the boss prefab.\n");
        return;
    }
    if (!dialog)
        return;
    dialog_add_line(dialog, NULL, "...", NULL);
    dialog_add_line(dialog, NULL, "Wait...", NULL);
    dialog_add_line(dialog, NULL, "...", NULL);
    dialog_add_line(dialog, NULL, "HELP US!!", NULL);
    dialog_add_line(dialog, NULL, "A T-REX APPEARED IN THE\n\
CENTER OF THE VILLAGE", NULL);
    dialog_add_line(dialog, NULL, "AHHHHHHHHHHHHHhh", NULL);
    dialog_add_line(dialog, NULL, "AHHHHHHHHhhhh", NULL);
    dialog_add_line(dialog, NULL, "HELPPPP", NULL);
}

void check_for_boss(gc_engine *engine)
{
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct player_component *inv;

    if (!player)
        return;
    inv = GETCMP(player, player_component);
    if (!inv->inventory_upgrades[0]
        || !inv->inventory_upgrades[1]
        || !inv->inventory_upgrades[2]
        || !inv->inventory_upgrades[3])
        return;
    spawn_boss(engine);
}

void boss_start(gc_engine *engine)
{
    combat_start(engine, "t-rex");
}
