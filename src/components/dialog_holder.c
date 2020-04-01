/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_holder.c
*/

#include "components/dialog_holder.h"
#include <stddef.h>
#include <malloc.h>

static void ctr(void *component, va_list args)
{
    struct dialog_holder *cmp = (struct dialog_holder *)component;

    cmp->text = va_arg(args, char **);
    cmp->single_usage = va_arg(args, int);
    cmp->has_seen = false;
    cmp->current_line = 0;
    cmp->current_text = NULL;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct dialog_holder *cmp = (struct dialog_holder *)component;
    int count = xml_getchildcount(n);

    cmp->single_usage = xml_getbool(n, "single_usage", false);
    cmp->text = malloc(sizeof(char *) * (count + 1));
    if (!cmp->text)
        return;
    n = n->child;
    for (int i = 0; n; n = n->next, i++)
        cmp->text[i] = xml_getproperty(n, "data");
    cmp->text[count] = NULL;
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