/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** fisherman.c
*/

#include "components/dialog_holder.h"
#include "systems/game_manager_system.h"
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
to come from the\nsource of the river, something must be there.", NULL);
    dialog_add_line(dialog, "Fisherman", "You should check it out!", NULL);
    dialog_add_line(dialog, "Fisherman", "If you pass nearby Mia, tell her\n\
that I will show up at...", NULL);
    dialog_add_line(dialog, "Fisherman", "her house for dinner tonight.", NULL);
    GETSYS(engine, game_manager_system)->has_message = true;
    return (true);
}