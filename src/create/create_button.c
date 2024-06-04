/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** create_button.c
*/

#include "csfml.h"

button_t *create_button(char *text, sfFloatRect rect, void (*function)(void))
{
    static int id = 0;
    button_t *new = MALLOC(sizeof(button_t));

    new->id = id;
    new->text = my_strdup(text);
    new->pos = (sfVector2f){rect.left, rect.top};
    new->state = (function == NULL) ? DISABLED : RELEASE;
    new->scale = (sfVector2f){rect.width, rect.height};
    new->function = function;
    return new;
}
