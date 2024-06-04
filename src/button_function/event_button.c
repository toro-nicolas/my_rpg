/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** event_button.c
*/

#include "csfml.h"

void event_button(button_t **buttons)
{
    sfVector2i mouse_pos = get_window()->mouse_pos;
    sfIntRect rect = {0};

    for (int i = 0; LEFTM == 2 && buttons[i] != NULL; i++) {
        if (buttons[i]->state == PRESSED) {
            buttons[i]->function();
            buttons[i]->state = RELEASE;
        }
    }
    for (int i = 0; LEFTM == 1 && buttons[i] != NULL; i++) {
        if (buttons[i]->state == PRESSED || buttons[i]->state == DISABLED)
            continue;
        rect = (sfIntRect){buttons[i]->pos.x - (222 * buttons[i]->scale.x) / 2,
        buttons[i]->pos.y - (108 * buttons[i]->scale.y) / 2,
        buttons[i]->scale.x * 222, buttons[i]->scale.y * 108};
        if (sfIntRect_contains(&rect, mouse_pos.x, mouse_pos.y))
            buttons[i]->state = PRESSED;
    }
}
