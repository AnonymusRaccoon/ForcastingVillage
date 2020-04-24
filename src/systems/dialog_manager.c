/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_manager.c
*/

#include <malloc.h>
#include "components/dialog_holder.h"
#include "engine.h"
#include "tile.h"

static void check_for_dialog(gc_engine *engine, va_list args)
{
    gc_keybindings key = va_arg(args, gc_keybindings);

    if (key != SPACE)
        return;
    dialog_next(engine);
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);
    struct dialog_manager *this = (struct dialog_manager *)system;

    engine->add_event_listener(engine, "key_pressed", &check_for_dialog);
    this->dialog_id = -1;
    this->input_id = -1;
    this->current_line = 0;
    this->current_text = NULL;
}

static void dtr(void *system, gc_engine *engine)
{
    engine->remove_event_listener(engine, "key_pressed", &check_for_dialog);
}

const struct dialog_manager dialog_manager = {
    base: {
        name: "dialog_manager",
        component_name: "dialog_holder",
        size: sizeof(struct dialog_manager),
        ctr: &ctr,
        dtr: &dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &update_entity,
        destroy: &system_destroy
    },
};