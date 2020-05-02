/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** mage.c
*/

#include "components/dialog_holder.h"
#include "components/player_component.h"
#include "engine.h"

void mage_give(gc_engine *engine)
{
    struct dialog_holder *dialog = dialog_get_current(engine);
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct player_component *inv;

    if (!player)
        return;
    inv = GETCMP(player, player_component);
    if (!inv)
        return;
    if (!inv->inventory_upgrades[1])
        dialog_add_line(dialog, "", "You got the fireball upgrade!", NULL);
    dialog->text[4] = NULL;
    inv->inventory_upgrades[1] = true;
}