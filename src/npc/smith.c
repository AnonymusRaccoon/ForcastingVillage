/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** smith.c
*/

#include <components/player_component.h>
#include <components/dialog_holder.h>
#include "engine.h"

bool smith_chest(gc_engine *engine, gc_entity *entity, \
gc_vector2 pos, enum gc_mousekeys key)
{
    struct dialog_holder *dialog = dialog_get_current(engine);
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct player_component *inv;

    if (!player)
        return (false);
    inv = GETCMP(player, player_component);
    if (!inv)
        return (false);
    dialog->text[1] = NULL;
    if (inv->inventory_upgrades[3])
        dialog_add_line(dialog, NULL, "This chest is empty.", NULL);
    else
        dialog_add_line(dialog, NULL, "You found the shield upgrade!", NULL);
    inv->inventory_upgrades[3] = true;
    return (true);
}