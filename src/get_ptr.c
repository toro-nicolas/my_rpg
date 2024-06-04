/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

user_variables_t *get_user(void)
{
    static user_variables_t user = {0};

    return &user;
}

window_info_t *get_window(void)
{
    static window_info_t window = {0};

    return &window;
}

thread_info_t *get_thread(void)
{
    static thread_info_t thread = {0};

    return &thread;
}

game_info_t *get_game(void)
{
    static game_info_t game = {0};

    if (game.text_chatbox == NULL)
        game.text_chatbox = create_text(5, "", get_font(), 50, sfBlack);
    return &game;
}
