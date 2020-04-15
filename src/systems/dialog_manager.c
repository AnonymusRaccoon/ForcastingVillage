/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_manager.c
*/

#include <malloc.h>
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
gc_scene *scene)
{
    struct renderer *rend;

    if (!text)
        return (true);
    rend = GETCMP(text, renderer);
    if (!rend || rend->type != GC_TXTREND || !rend->data)
        return (true);
    if (((gc_text *)rend->data)->text)
        free(((gc_text *)rend->data)->text);
    this->current_text = this->current_dialog->text[this->current_line];
    if (this->current_text)
        ((gc_text *)rend->data)->text = my_strdup(this->current_text);
    else
        ((gc_text *)rend->data)->text = NULL;
    this->current_line++;
    return (!this->current_text);
}

static void check_for_dialog(gc_engine *engine, va_list args)
{
    struct dialog_manager *this = GETSYS(engine, dialog_manager);
    gc_keybindings key = va_arg(args, gc_keybindings);
    gc_scene *scene = engine->scene;
    gc_entity *entity = scene->get_entity(scene, 50);

    if (key != SPACE || !entity)
        return;
    if (this->dialog_id == -1)
        load_dialog(this, engine, entity);
    entity = scene->get_entity(scene, 1337);
    if (!update_dialog(this, entity, scene))
        return;
    for (gc_list *li = scene->entities; li; li = li->next) {
        if (((gc_entity *) li->data)->prefab_id == this->dialog_id)
            ((gc_entity *) li->data)->destroy(li->data, scene);
    }
    this->dialog_id = -1;
}

static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);
    struct dialog_manager *dima = (struct dialog_manager *)system;

    engine->add_event_listener(engine, "key_pressed", &check_for_dialog);
    dima->dialog_id = -1;
    dima->current_line = 0;
    dima->current_text = NULL;
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