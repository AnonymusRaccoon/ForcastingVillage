/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** fisherman.c
*/

#include "components/dialog_holder.h"
#include "systems/game_manager_system.h"
#include "components/player_component.h"
#include "engine.h"


void fisherman_setup(gc_engine *engine)
{
    struct dialog_holder *holder = dialog_get_current(engine);

    holder->text[2] = NULL;
}

bool fisherman_next(gc_engine *engine, gc_entity *entity, \
gc_vector2 pos, enum gc_mousekeys key)
{
    struct dialog_holder *dialog = dialog_get_current(engine);

    if (!dialog)
        return (false);
    dialog_add_line(dialog, "Fisherman", "Sometimes I catch \
fishes with\na strange ability:", NULL);
    dialog_add_line(dialog, "Fisherman", "they can throw a powerful Water\n\
Jet at their enemies.", NULL);
    dialog_add_line(dialog, "Fisherman", "This kind of fish seems \
to come\nfrom thesource of the river.", NULL);
    dialog_add_line(dialog, "Fisherman", "Something must be there.\n\
You should check it out!", NULL);
    dialog_add_line(dialog, "Fisherman", "If you pass nearby Mia, tell her\n\
that I will show up at...", NULL);
    dialog_add_line(dialog, "Fisherman", "her house for dinner tonight.", NULL);
    GETSYS(engine, game_manager_system)->has_message = true;
    return (true);
}

bool fisherman_chest(gc_engine *engine, gc_entity *entity, \
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
    if (inv->inventory_upgrades[1])
        dialog_add_line(dialog, NULL, "This chest is empty.", NULL);
    else
        dialog_add_line(dialog, "", "You found the water jet upgrade!", NULL);
    inv->inventory_upgrades[1] = true;
    return (true);
}