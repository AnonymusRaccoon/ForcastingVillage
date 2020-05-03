/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_methods.c
*/

#include "components/dialog_holder.h"
#include "utility.h"
#include <malloc.h>

struct dialog_line *dialog_add_line(struct dialog_holder *this, char *name, \
char *text, struct dialog_input *inputs)
{
    struct dialog_line *line = malloc(sizeof(*line));
    int count = 0;

    if (!line)
        return (NULL);
    line->name = name;
    line->text = text;
    if (inputs)
        for (count = 0; inputs[count].text; count++);
    line->input_count = count;
    line->inputs = inputs;
    line->callback = NULL;
    for (count = 0; this->text[count]; count++);
    this->text = my_realloc(this->text, (count + 1) * sizeof(void *), \
(count + 2) * sizeof(void *));
    if (!this->text)
        return (NULL);
    this->text[count] = line;
    this->text[count + 1] = NULL;
    return (line);
}

struct dialog_holder *dialog_get_current(gc_engine *engine)
{
    struct dialog_manager *manager = GETSYS(engine, dialog_manager);

    return (manager->current_dialog);
}