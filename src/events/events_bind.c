/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void analyse_key_pressed_bind(sfEvent event)
{
    for (int i = 1; get_bind()->binding != NULL && i < 102; i++) {
        if (get_keys()->keys[i]) {
            *(get_bind()->binding) = i;
            get_bind()->binding = NULL;
            return;
        }
    }
    if (ESCAPEK) {
        get_game()->cur_state = PAUSE;
        get_game()->old_state = MENU;
        ESCAPEK = 0;
    }
}

void events_bind(sfEvent event)
{
    analyse_key_pressed_bind(event);
    event_button(get_buttons_bind());
}
