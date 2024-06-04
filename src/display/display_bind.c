/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void print_bind_help(sfText *text, char *str[], char *bind[])
{
    unsigned char *key = (unsigned char *)get_bind();

    for (int i = 0; i < 11; i++) {
        sfText_setPosition(text, (sfVector2f){500 + 560 * (i / 6),
        290 + 100 * (i % 6)});
        sfText_setString(text, str[i]);
        sfRenderWindow_drawText(get_window()->window, text, NULL);
        sfText_setString(text, bind[(get_bind()->binding == key + i + 8)
        ? 0 : key[i + 8]]);
        sfText_setPosition(text, (sfVector2f){840 + 560 * (i / 6)
        - sfText_getGlobalBounds(text).width / 2, 285 + 100 * (i % 6)});
        sfRenderWindow_drawText(get_window()->window, text, NULL);
    }
}

static void print_bind(sfText *text)
{
    static char *str[] =
        {"Move Left", "Move Right", "Move up", "Move Down",
        "Attack", "Pause", "Interact", "Slot 1",
        "Slot 2", "Slot 3", "Inventory", NULL};
    static char *bind[] =
        {"...", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
        "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "ESC", "Ctrl-L",
        "Shift-L", "Alt-L", "Win", "Ctrl-R", "Shift-R", "Alt-R", "Win", "Menu",
        "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Space",
        "Enter", "Return", "Tab", "Page Up", "Page Down", "End", "Home",
        "Insert", "Delete", "+ Pad", "- Pad", "* Pad", "/ Pad", "Left Arrow",
        "Right Arrow", "Up Arrow", "Down Arrow", "0 Pad", "1 Pad", "2 Pad",
        "3 Pad", "4 Pad", "5 Pad", "6 Pad", "7 Pad", "8 Pad", "9 Pad", "F1",
        "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
        "F13", "F14", "F15", "Pause", NULL};

    print_bind_help(text, str, bind);
}

static void display_bind_help(void)
{
    static sfSprite *sprite = NULL;
    static sfText *text = NULL;

    if (sprite == NULL)
        sprite = sfSprite_create();
    if (text == NULL) {
        text = sfText_create();
        sfText_setFont(text, get_font());
    }
    sfSprite_setTextureRect(sprite, (sfIntRect){0, 2160, 629, 392});
    sfSprite_setPosition(sprite, (sfVector2f){331, 148});
    sfSprite_setScale(sprite, V2F {2, 2});
    sfSprite_setTexture(sprite, get_game()->main_texture, sfFalse);
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    display_button(get_buttons_bind());
    print_bind(text);
}

void display_bind(void)
{
    if (get_game()->old_state == PAUSE) {
        display_main();
        display_bind_help();
    }
}
