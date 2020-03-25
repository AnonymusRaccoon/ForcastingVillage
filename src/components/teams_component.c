/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** camera_follow
*/

#include "xml.h"
#include "component.h"
#include "components/teams_component.h"
#include "utility.h"
#include <stdlib.h>

static void ctr(void *component, va_list args)
{
    struct teams_component *cmp = (struct teams_component *)component;

    cmp->delay = va_arg(args, double);
    cmp->next_teams = cmp->delay;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct teams_component *cmp = (struct teams_component *)component;

    cmp->delay = xml_getfloatprop(n, "delay");
    cmp->next_teams = cmp->delay;
    cmp->prefab_count = xml_getchildcount_filtered(n, "prefab");
    cmp->prefabs = malloc(sizeof(char *) * cmp->prefab_count);
    cmp->prefabs_size = malloc(sizeof(int) * cmp->prefab_count);
    n = n->child;
    if (!cmp->prefabs || !cmp->prefab_count) {
        cmp->prefabs = NULL;
        cmp->prefabs_size = NULL;
        cmp->prefab_count = 0;
        return;
    }
    for (int i = 0; i < cmp->prefab_count; i++) {
        cmp->prefabs[i] = xml_getproperty(n, "src");
        cmp->prefabs_size[i] = xml_getintprop(n, "height");
        n = n->next;
    }
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

const struct teams_component teams_component = {
    base: {
        name: "teams_component",
        size: sizeof(struct teams_component),
        dependencies: (char *[]) {
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};