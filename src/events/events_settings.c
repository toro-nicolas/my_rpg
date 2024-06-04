/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void check_slider(sfVector2i mouse)
{
    static char slider = 0;

    if (LEFTM == 2)
        slider = 0;
    if (slider == 1) {
        get_window()->vol_music = ((float)mouse.x - 843) * 100 / 423.6;
        get_window()->vol_music = MIN(100, get_window()->vol_music);
        get_window()->vol_music = MAX(0, get_window()->vol_music);
    } else if (slider == 2) {
        get_window()->vol_fx = ((float)mouse.x - 843) * 100 / 423.6;
        get_window()->vol_fx = MIN(100, get_window()->vol_fx);
        get_window()->vol_fx = MAX(0, get_window()->vol_fx);
    }
    update_volume();
    for (int i = 0; LEFTM == 1 && i < 2 && slider == 0; i++)
        if (843 < (float)mouse.x && (843 + 423.6) > (float)mouse.x
        && (282 + 100 * i) < (float)mouse.y
        && ((282 + 100 * i) + 46) > (float)mouse.y)
            slider = i + 1;
    event_button(get_buttons_settings());
}

static int set_fps(int fps)
{
    if (fps == 0)
        return 30;
    if (fps == 1)
        return 60;
    if (fps == 2)
        return 120;
    if (fps == 3)
        return 0;
}

static void set_size(int i, window_info_t *window)
{
    if ((i == 0 && window->size != 0) || (i != 0 && window->size == 0)) {
        sfRenderWindow_destroy(window->window);
        if (i != 0 && window->size == 0) {
            window->window
            = sfRenderWindow_create(window->video_mode, "Drysfa Xaar",
            sfClose, NULL);
            sfRenderWindow_setPosition(window->window, window->position);
        } else {
            window->window
            = sfRenderWindow_create(sfVideoMode_getDesktopMode(),
            "Drysfa Xarr", 0, NULL);
            sfRenderWindow_setPosition(window->window, (sfVector2i){0, 0});
        }
        sfRenderWindow_setView(window->window, window->view);
        sfRenderWindow_setFramerateLimit(window->window, window->framerate);
    }
    if (i == 1 && window->size != i)
        sfRenderWindow_setSize(window->window, (sfVector2u){1920, 1080});
    if (i == 2 && window->size != i)
        sfRenderWindow_setSize(window->window, (sfVector2u){1280, 720});
}

static void analyse_key_pressed_settings(sfEvent event)
{
    if (ESCAPEK) {
        get_game()->cur_state = get_game()->old_state;
        get_game()->old_state = SETTINGS;
        ESCAPEK = 0;
    }
}

void events_settings(sfEvent event)
{
    sfVector2i mouse_pos = get_window()->mouse_pos;
    sfIntRect rect = {0};

    analyse_key_pressed_settings(event);
    for (int i = 0; LEFTM == 1 && i < 4; i++) {
        rect = (sfIntRect){603 + 138 + 120 * i, 148 + 412, 196, 76};
        if (sfIntRect_contains(&rect, mouse_pos.x, mouse_pos.y)) {
            get_window()->framerate = set_fps(i);
            sfRenderWindow_setFramerateLimit(get_window()->window,
            get_window()->framerate);
        }
    }
    for (int i = 0; LEFTM == 1 && i < 3; i++) {
        rect = (sfIntRect){503 + 138 + 220 * i, 148 + 612, 196, 76};
        if (sfIntRect_contains(&rect, mouse_pos.x, mouse_pos.y)) {
            set_size(i, get_window());
            get_window()->size = i;
        }
    }
    check_slider(mouse_pos);
}
