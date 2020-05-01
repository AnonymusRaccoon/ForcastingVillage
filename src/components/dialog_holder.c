/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_holder.c
*/

#include "components/dialog_holder.h"
#include <stddef.h>
#include <malloc.h>
#include "components/vertex_component.h"
#include "map_utils.h"
#include "my.h"

void setup_tile_interactions(struct dialog_holder *this, gc_scene *scene, \
gc_vector2i pos, char *tile_texture)
{
    gc_list *maps = scene->get_entity_by_cmp(scene, "vertex_component");
    struct vertex_component *map;
    struct tile *tile;

    if (!maps)
        return;
    map = GETCMP(maps[0].data, vertex_component);
    if (!map || !map->map)
        return;
    tile = get_tile_at(map, pos);
    if (!tile)
        return;
    if (tile->type)
        my_printf("Warning, a dialog is overriding a custom tile type: %s\n", \
tile->type);
    tile->type = "dialog";
    if (tile->texture)
        tile->texture = scene->get_data(scene, "sprite", tile_texture);
    this->tile = tile;
}

static void ctr(void *component, va_list args)
{
    struct dialog_holder *cmp = (struct dialog_holder *)component;
    gc_scene *scene = va_arg(args, gc_scene *);
    int x;
    int y;
    char *texture;

    if (!scene)
        return;
    cmp->text = va_arg(args, struct dialog_line **);
    cmp->single_usage = va_arg(args, int);
    cmp->has_seen = false;
    x = va_arg(args, int);
    y = va_arg(args, int);
    texture = va_arg(args, char *);
    setup_tile_interactions(cmp, scene, (gc_vector2i){x, y}, texture);
}

bool dialog_parse_inputs(struct dialog_line *txt, gc_scene *scene, node *n)
{
    char *click;
    int i = 0;

    txt->inputs = malloc(sizeof(struct dialog_input) * txt->input_count);
    if (!txt->inputs)
        return (false);
    for (n = n->child; n; n = n->next) {
        txt->inputs[i].text = xml_getproperty(n, "text");
        click = xml_gettempprop(n, "click");
        if (click)
            txt->inputs[i].callback = scene->get_data(scene, "input", click);
        else
            txt->inputs[i].callback = NULL;
        if (!txt->inputs[i++].callback && click)
            my_printf("Couldn't find an input with the name: %s.\n", click);
    }
    return (false);
}

struct dialog_line *dialog_parse_text(gc_scene *scene, node *n)
{
    struct dialog_line *txt = malloc(sizeof(struct dialog_line));
    char *callback;

    if (!txt)
        return (NULL);
    txt->name = my_strdup(n->name);
    txt->text = xml_getproperty(n, "line");
    txt->input_count = xml_getchildcount_filtered(n, "input");
    callback = xml_gettempprop(n, "callback");
    txt->callback = scene->get_data(scene, "dialog_callback", callback);
    if (callback && !txt->callback)
        my_printf("Couldn't find an callback with the name: %s.\n", callback);
    txt->inputs = NULL;
    if (txt->input_count == 0)
        return (txt);
    dialog_parse_inputs(txt, scene, n);
    return (txt);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct dialog_holder *cmp = (struct dialog_holder *)component;
    int count = xml_getchildcount(n);
    int x = xml_getintprop(n, "x");
    int y = xml_getintprop(n, "y");
    char *texture = xml_gettmpstring(n, "tile_texture", NULL);

    cmp->single_usage = xml_getbool(n, "single_usage", false);
    cmp->text = malloc(sizeof(struct dialog_line *) * (count + 1));
    if (!cmp->text)
        return;
    n = n->child;
    for (int i = 0; n; n = n->next, i++)
        cmp->text[i] = dialog_parse_text(scene, n);
    cmp->text[count] = NULL;
    setup_tile_interactions(cmp, scene, (gc_vector2i){x, y}, texture);
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct dialog_holder dialog_holder = {
    base: {
        name: "dialog_holder",
        size: sizeof(struct dialog_holder),
        dependencies: (char *[]){
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: NULL,
        serialize: &serialize,
        destroy: &component_destroy
    }
};