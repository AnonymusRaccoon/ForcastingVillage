/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** dialog_methods.c
*/

#include "components/dialog_holder.h"
#include "utility.h"
#include <malloc.h>

void dialog_add_line(struct dialog_holder *this, char *name, char *text, \
struct dialog_input *inputs)
{
    struct dialog_line *line = malloc(sizeof(*line));
    int count = 0;

    if (!line)
        return;
    line->name = name;
    line->text = text;
    if (inputs)
        for (count = 0; &inputs[count]; count++);
    line->input_count = count;
    line->inputs = inputs;
    for (count = 0; this->text[count]; count++);
    this->text = my_realloc(this->text, count, count + sizeof(void *));
    if (!this->text)
        return;
    this->text[count] = line;
    this->text[count + 1] = NULL;
}