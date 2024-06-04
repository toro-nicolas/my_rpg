/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void analyse_key_pressed_pause(sfEvent event)
{
    if (ESCAPEK) {
        get_game()->cur_state = MAIN;
        get_game()->old_state = PAUSE;
        ESCAPEK = 0;
    }
}

void events_pause(sfEvent event)
{
    analyse_key_pressed_pause(event);
    event_button(get_buttons_pause());
}
