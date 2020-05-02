/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** lumberjack.c
*/

#include <components/player_component.h>
#include <components/dialog_holder.h>
#include "engine.h"

void lumberjack_delete(gc_engine *engine)
{
    struct dialog_holder *dialog = dialog_get_current(engine);

    dialog->text[3] = NULL;
}

bool lumberjack_yes(gc_engine *engine, gc_entity *entity, \
gc_vector2 pos, enum gc_mousekeys key)
{
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct dialog_holder *dialog = dialog_get_current(engine);
    struct dialog_line *di;
    struct player_component *inv;

    if (!player)
        return (false);
    inv = GETCMP(player, player_component);
    inv->inventory_upgrades[2] = true;
    di = dialog_add_line(dialog, "", "You gained the uppercut upgrade!", NULL);
    di->callback = &lumberjack_delete;
    return (true);
}