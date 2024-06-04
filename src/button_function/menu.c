/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** menu.c
*/

#include "csfml.h"

static void update_button_state(button_t *buttons)
{
    if (buttons->state != DISABLED)
        return;
    if (save_found())
        buttons->state = RELEASE;
    else
        buttons->state = DISABLED;
}

button_t **get_buttons_menu(void)
{
    static button_t **buttons = NULL;

    if (!buttons) {
        buttons = MALLOC(sizeof(button_t *) * (4 + 1));
        buttons[0] = create_button("Play", (sfFloatRect){960, 550, 2, 1},
        &menu_play);
        buttons[1] = create_button("Resume", (sfFloatRect){960, 670, 2, 1},
        ((save_found()) ? &menu_resume : NULL));
        buttons[2] = create_button("Setting", (sfFloatRect){960, 790, 2, 1},
        &menu_settings);
        buttons[3] = create_button("Quit", (sfFloatRect){960, 910, 2, 1},
        &menu_quit);
        buttons[4] = NULL;
    }
    update_button_state(buttons[1]);
    return buttons;
}

void menu_play(void)
{
    get_game()->cur_state = INTRO;
    get_game()->old_state = MENU;
}

void menu_resume(void)
{
    load_save();
    get_game()->old_state = MENU;
    get_game()->cur_state = MAIN;
}

void menu_settings(void)
{
    get_game()->cur_state = SETTINGS;
    get_game()->old_state = MENU;
}

void menu_quit(void)
{
    get_game()->cur_state = EXIT;
    get_game()->old_state = MENU;
}
