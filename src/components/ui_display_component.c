/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** ui display component
*/

#include "xml.h"
#include "component.h"
#include "components/ui_display_component.h"

static void ui_display_ctr(void *component, va_list args)
{
    struct ui_display_component *cmp = (struct ui_display_component *)\
component;
    (void)args;
}

static void ui_display_fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
    struct ui_display_component *cmp = (struct ui_display_component *)\
component;

    (void)scene;
    (void)entity;
    (void)n;
}

static void ui_display_dtr(void *component)
{
    (void)component;
}

static char *ui_display_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct ui_display_component ui_display_component = {
        base: {
                name: "ui_display_component",
                size: sizeof(struct ui_display_component),
                dependencies: (char *[]){
                        NULL
                },
                ctr: &ui_display_ctr,
                fdctr: &ui_display_fdctr,
                dtr: &ui_display_dtr,
                serialize: &ui_display_serialize,
                destroy: &component_destroy
        }
};