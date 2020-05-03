/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** inventory
*/

#include "list.h"
#include "scene.h"
#include "sprite.h"
#include "prefab.h"
#include "components/player_component.h"
#include "components/renderer.h"
#include "components/tag_component.h"
#include "my.h"

void display_inv_slot(gc_scene *scene, struct renderer *rend, int nb)
{
    gc_sprite *sprite = NULL;
    char *textures[5] = {"empty_slot", "slot_1", "slot_2", "slot_3", "slot_4"};
    gc_list *li = scene->get_entity_by_cmp(scene, "player_component");
    struct player_component *cmp;

    if (!li)
        return;
    cmp = GETCMP(li->data, player_component);
    if (!cmp->inventory_upgrades[nb - 1])
        nb = 0;
    sprite = scene->get_data(scene, "sprite", textures[nb]);
    if (sprite)
        ((gc_sprite *)rend->data)->texture = sprite;
}

bool toggle_inventory(gc_engine *engine)
{
    gc_scene *scene = engine->scene;
    gc_list *list;

    scene->is_paused = !scene->is_paused;
    if (scene->is_paused) {
        prefab_load(engine, "prefabs/inventory.gcprefab");
        return (true);
    }
    list = scene->get_entity_by_cmp(scene, "tag_component");
    for (gc_list *li = list; li; li = li->next) {
        if (!my_strcmp(GETCMP(li->data, \
tag_component)->tag, "inventory"))
            ((gc_entity *)li->data)->destroy(li->data, scene);
    }
    return (true);
}