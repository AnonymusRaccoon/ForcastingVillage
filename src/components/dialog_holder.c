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
    cmp->text = va_arg(args, char **);
    cmp->single_usage = va_arg(args, int);
    cmp->has_seen = false;
    x = va_arg(args, int);
    y = va_arg(args, int);
    texture = va_arg(args, char *);
    setup_tile_interactions(cmp, scene, (gc_vector2i){x, y}, texture);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct dialog_holder *cmp = (struct dialog_holder *)component;
    int count = xml_getchildcount(n);
    int x = xml_getintprop(n, "x");
    int y = xml_getintprop(n, "y");
    char *texture = xml_gettmpstring(n, "tile_texture", NULL);

    cmp->single_usage = xml_getbool(n, "single_usage", false);
    cmp->text = malloc(sizeof(char *) * (count + 1));
    if (!cmp->text)
        return;
    n = n->child;
    for (int i = 0; n; n = n->next, i++)
        cmp->text[i] = xml_getproperty(n, "line");
    cmp->text[count] = NULL;
    setup_tile_interactions(cmp, scene, (gc_vector2i){x, y}, texture);
}

static void dtr(void *component)
{
    (void)component;
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
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};