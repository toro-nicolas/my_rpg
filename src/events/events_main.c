/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void analyse_key_pressed_main(sfEvent event)
{
    item_t *item = NULL;

    if (HITBOXK) {
        get_user()->show_hitbox = !get_user()->show_hitbox;
        HITBOXK = 0;
    }
    if (PAUSEK) {
        get_game()->cur_state = PAUSE;
        get_game()->old_state = MAIN;
        ESCAPEK = 0;
    }
}

void analyse_key_released_main(sfEvent event)
{
    return;
}

void events_main(sfEvent event)
{
    analyse_key_pressed_main(event);
    analyse_key_released_main(event);
    events_player(event);
}
