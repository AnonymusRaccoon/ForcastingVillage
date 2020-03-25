/*
** EPITECH PROJECT, 2020
** DPR
** File description:
** game_stats
*/

#include <components/renderer.h>
#include <text.h>
#include "dpr_errors.h"
#include "xml.h"
#include "component.h"
#include "utility.h"
#include "components/game_display.h"
#include <malloc.h>

static void ctr(void *component, va_list args)
{
    struct game_display *cmp = (struct game_display *)component;

    cmp->type = va_arg(args, display_type_enum);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct game_display *cmp = (struct game_display *)component;
    struct renderer *rend = GETCMP(entity, renderer);
    char *display_type = xml_gettempprop(n, "stats");

    if (!my_strcmp(display_type, "selected_tile")) {
        cmp->type = SELECT_TILE_DISPLAY;
        return;
    }
    if (!my_strcmp(display_type, "happiness"))
        cmp->type = HAPPINESS_DISPLAY;
    else
        cmp->type = STUPIDITY_DISPLAY;
    if (!rend || rend->type != GC_TXTREND) {
        my_printf("Using a game display without a text renderer.\n");
        return;
    }
    ((gc_text *)rend->data)->text = malloc(sizeof(char) * 10);
    if (((gc_text *)rend->data)->text)
        ((gc_text *)rend->data)->text[0] = '\0';
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

const struct game_display game_display = {
    base: {
        name: "game_display",
        size: sizeof(struct game_display),
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