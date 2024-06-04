/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** menu.c
*/

#include "csfml.h"

static void set_bind_help(button_t **buttons)
{
    buttons[6] = create_button("", (sfFloatRect){840, 810, 1, 0.7},
    &bind_pause);
    buttons[7] = create_button("", (sfFloatRect){1400, 310, 1, 0.7},
    &bind_interact);
    buttons[8] = create_button("", (sfFloatRect){1400, 410, 1, 0.7},
    &bind_slot1);
    buttons[9] = create_button("", (sfFloatRect){1400, 510, 1, 0.7},
    &bind_slot2);
    buttons[10] = create_button("", (sfFloatRect){1400, 610, 1, 0.7},
    &bind_slot3);
    buttons[11] = create_button("", (sfFloatRect){1400, 710, 1, 0.7},
    &bind_inv);
}

button_t **get_buttons_bind(void)
{
    static button_t **buttons = NULL;

    if (!buttons) {
        buttons = CALLOC(sizeof(button_t *) * (12 + 1));
        buttons[0] = create_button("Quit", (sfFloatRect){960, 910, 2, 1},
        &bind_quit);
        buttons[1] = create_button("", (sfFloatRect){840, 310, 1, 0.7},
        &bind_left);
        buttons[2] = create_button("", (sfFloatRect){840, 410, 1, 0.7},
        &bind_right);
        buttons[3] = create_button("", (sfFloatRect){840, 510, 1, 0.7},
        &bind_up);
        buttons[4] = create_button("", (sfFloatRect){840, 610, 1, 0.7},
        &bind_down);
        buttons[5] = create_button("", (sfFloatRect){840, 710, 1, 0.7},
        &bind_attack);
        set_bind_help(buttons);
    }
    return buttons;
}

void bind_quit(void)
{
    get_game()->cur_state = get_game()->old_state;
    get_game()->old_state = SETTINGS;
    get_bind()->binding = NULL;
}

void bind_left(void)
{
    get_bind()->binding = &(get_bind()->left);
}

void bind_right(void)
{
    get_bind()->binding = &(get_bind()->right);
}

void bind_up(void)
{
    get_bind()->binding = &(get_bind()->up);
}
