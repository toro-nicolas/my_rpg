/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** menu.c
*/

#include "csfml.h"

button_t **get_buttons_settings(void)
{
    static button_t **buttons = NULL;

    if (!buttons) {
        buttons = MALLOC(sizeof(button_t *) * (1 + 1));
        buttons[0] = create_button("Quit", (sfFloatRect){960, 910, 2, 1},
        &settings_quit);
        buttons[1] = NULL;
    }
    return buttons;
}

void settings_quit(void)
{
    get_game()->cur_state = get_game()->old_state;
    get_game()->old_state = SETTINGS;
}
