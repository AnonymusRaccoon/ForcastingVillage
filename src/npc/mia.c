/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** mia.c
*/

#include <components/health_component.h>
#include <components/dialog_holder.h>
#include "engine.h"

struct dialog_holder *dialog_get_current(gc_engine *engine)
{
    struct dialog_manager *manager = GETSYS(engine, dialog_manager);

    return (manager->current_dialog);
}

void mia_setup(gc_engine *engine)
{
    struct dialog_holder *holder = dialog_get_current(engine);

    holder->text[2] = NULL;
}

bool mia_heal(gc_engine *engine, gc_entity *entity, \
gc_vector2 pos, enum gc_mousekeys key)
{
    gc_entity *player = engine->scene->get_entity(engine->scene, 50);
    struct health_component *hea;
    struct dialog_holder *dialog = dialog_get_current(engine);

    if (!player || !dialog)
        return (false);
    hea = GETCMP(player, health_component);
    if (!hea)
        return (false);
    if (hea->health != hea->health_max) {
        hea->health = hea->health_max;
        dialog_add_line(dialog, "Mia", "Of course, let me\
take care\nof it.", NULL);
    } else {
        dialog_add_line(dialog, "Mia", "You don't seem to have\n\
any wounds.", NULL);
        dialog_add_line(dialog, "Mia", "Are you sure you are\n\
here for that?", NULL);
    }
    return (true);
}