/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void check_key(sfEvent event, int value)
{
    if (event.key.code == -1)
        return;
    get_keys()->keys[event.key.code + 1] = value;
}

static void call_events(window_info_t *window, sfEvent event,
    game_info_t *game, void (*function)(sfEvent))
{
    window->mouse_pos.x = sfMouse_getPositionRenderWindow(window->window).x
    * (1920.0 / sfRenderWindow_getSize(window->window).x);
    window->mouse_pos.y = sfMouse_getPositionRenderWindow(window->window).y
    * (1080.0 / sfRenderWindow_getSize(window->window).y);
    if (window->size != 0)
        window->position = sfRenderWindow_getPosition(window->window);
    if (game->cur_state != EXIT)
        function(event);
}

void analyse_events(void)
{
    window_info_t *window = get_window();
    sfEvent event = window->event;
    game_info_t *game = get_game();
    void (*events[])(sfEvent) = {&events_intro, &events_menu, &events_main,
    &events_pause, &events_settings, &events_bind, NULL};

    get_keys()->keys[0] = 0;
    while (sfRenderWindow_pollEvent(window->window, &event)) {
        if (event.type == sfEvtKeyPressed || event.type == sfEvtKeyReleased)
            check_key(event, 6 - event.type);
        if ((event.type == sfEvtMouseButtonPressed
        || event.type == sfEvtMouseButtonReleased)
        && event.mouseButton.button == 0)
            get_keys()->keys[0] = event.type - 8;
        if (event.type == sfEvtClosed)
            game->cur_state = EXIT;
    }
    call_events(window, event, game, events[game->cur_state]);
}
