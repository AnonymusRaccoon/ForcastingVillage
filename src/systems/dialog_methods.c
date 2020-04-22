/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_methods.c
*/

#include <malloc.h>
#include <components/controllable_component.h>
#include "components/map_linker.h"
#include "text.h"
#include "my.h"
#include "components/dialog_holder.h"
#include "components/renderer.h"
#include "prefab.h"
#include "engine.h"
#include "tile.h"

void load_dialog(struct dialog_manager *this, gc_engine *engine, \
gc_entity *player)
{
    struct map_linker *link = GETCMP(player, map_linker);
    gc_scene *scene = engine->scene;
    gc_list *holders = scene->get_entity_by_cmp(scene, "dialog_holder");
    struct dialog_holder *dialog;

    if (!link || !link->tile || !link->tile->type || \
my_strcmp(link->tile->type, "dialog"))
        return;
    this->dialog_id = prefab_load(engine, "prefabs/dialog.gcprefab");
    if (this->dialog_id < 0)
        my_printf("Couldn't load the dialog prefab.\n");
    for (; holders; holders = holders->next) {
        dialog = GETCMP(holders->data, dialog_holder);
        if (dialog->tile == link->tile)
            this->current_dialog = dialog;
    }
    if (!this->current_dialog)
        return;
    this->current_text = this->current_dialog->text[0];
    this->current_line = 0;
}

bool update_dialog(struct dialog_manager *this, gc_entity *text, \
gc_entity *name)
{
    struct renderer *rend = GETCMP(name, renderer);

    this->current_text = this->current_dialog->text[this->current_line];
    if (!rend || rend->type != GC_TXTREND || !rend->data)
        return (true);
    rend->destroy = &text_safe_destroy;
    if (this->current_text)
        ((gc_text *)rend->data)->text = this->current_text->name;
    else
        ((gc_text *)rend->data)->text = NULL;
    rend = GETCMP(text, renderer);
    if (!rend || rend->type != GC_TXTREND || !rend->data)
        return (true);
    rend->destroy = &text_safe_destroy;
    if (this->current_text) {
        ((gc_text *) rend->data)->text = this->current_text->text;
        this->current_input = &this->current_text->inputs[0];
    } else
        ((gc_text *)rend->data)->text = NULL;
    this->current_line++;
    return (!this->current_text);
}

static bool handle_input(gc_engine *engine, struct dialog_manager *this)
{
    gc_entity *entity;
    struct renderer *rend;

    if (!this->current_text->inputs)
        return (true);
    this->input_id = prefab_load(engine, "prefabs/input.gcprefab");
    if (this->input_id < 0) {
        my_printf("Couldn't load the input prefab.\n");
        return (false);
    }
    for (int i = 0; i < this->current_text->input_count; i++) {
        entity = engine->scene->get_entity(engine->scene, 35353500 + i);
        if (!entity)
            return (false);
        if (!(rend = GETCMP(entity, renderer)) || rend->type != GC_TXTREND)
            return (false);
        ((gc_text *)rend->data)->text = this->current_text->inputs[i].text;
        rend->destroy = &text_safe_destroy;
    }
    return (true);
}

void run_input_func(struct dialog_manager *this, gc_engine *engine)
{
    if (this->current_input->callback)
        this->current_input->callback(engine, this->input_index);
    prefab_destroy(engine->scene, this->input_id);
    this->input_id = -1;
}

void dialog_next(gc_engine *engine)
{
    struct dialog_manager *this = GETSYS(engine, dialog_manager);
    gc_scene *scene = engine->scene;
    gc_entity *entity = scene->get_entity(scene, 50);
    gc_entity *holder_name;

    if (!entity)
        return;
    if (this->dialog_id == -1)
        load_dialog(this, engine, entity);
    if (this->input_id >= 0)
        run_input_func(this, engine);
    controllable_set_can_move(scene, false);
    holder_name = scene->get_entity(scene, 1336);
    entity = scene->get_entity(scene, 1337);
    if (!entity || !holder_name
    ||!update_dialog(this, entity, holder_name) && handle_input(engine, this))
        return;
    prefab_destroy(scene, this->dialog_id);
    this->dialog_id = -1;
    controllable_set_can_move(scene, true);
    engine->trigger_event(engine, "dialog_ended");
}
