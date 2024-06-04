/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** menu.c
*/

#include "csfml.h"

static void pause_save(void)
{
    save_game();
}

static void pause_loading(void)
{
    load_save();
    get_game()->cur_state = MAIN;
    get_game()->old_state = PAUSE;
}

static void update_button_state(button_t *buttons)
{
    if (buttons->state != DISABLED)
        return;
    if (save_found())
        buttons->state = RELEASE;
    else
        buttons->state = DISABLED;
}

button_t **get_buttons_pause(void)
{
    static button_t **buttons = NULL;

    if (!buttons) {
        buttons = CALLOC(sizeof(button_t *) * (6 + 1));
        buttons[0] = create_button("Resume", (sfFloatRect){960, 430, 2, 1},
        &pause_resume);
        buttons[1] = create_button("Save", (sfFloatRect){849, 550, 1, 1},
        &pause_save);
        buttons[2] = create_button("Loading", (sfFloatRect){1071, 550, 1, 1},
        ((save_found()) ? &pause_loading : NULL));
        buttons[3] = create_button("Command", (sfFloatRect){960, 670, 2, 1},
        &pause_bind);
        buttons[4] = create_button("Setting", (sfFloatRect){960, 790, 2, 1},
        &pause_settings);
        buttons[5] = create_button("Menu", (sfFloatRect){960, 910, 2, 1},
        &pause_menu);
    }
    update_button_state(buttons[2]);
    return buttons;
}

void pause_resume(void)
{
    get_game()->cur_state = MAIN;
    get_game()->old_state = PAUSE;
}

void pause_settings(void)
{
    get_game()->cur_state = SETTINGS;
    get_game()->old_state = PAUSE;
}

void pause_menu(void)
{
    play_music(MUSIC_MENU);
    get_game()->cur_state = MENU;
    get_game()->text_chatbox = create_text(5, "", get_font(), 50, sfBlack);
    display_talk(1);
    remove_mobs_fl();
    get_game()->old_state = PAUSE;
}

void pause_bind(void)
{
    get_game()->cur_state = BIND;
    get_game()->old_state = PAUSE;
}
