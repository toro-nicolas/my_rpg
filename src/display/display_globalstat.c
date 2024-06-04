/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void stick_icon(char *rect, sfVector2f pos)
{
    sfFloatRect rect_text = sfText_getGlobalBounds(get_game()->text_chatbox);
    sfSprite *sprite = get_entity("levelup_sprite")->sprite;
    sfVector2f scale = sfSprite_getScale(sprite);

    sfSprite_setTextureRect(sprite, get_stat_rect(rect));
    sfSprite_setPosition(sprite,
        V2F {pos.x + rect_text.width + 20, pos.y + 15});
    sfSprite_setScale(sprite, V2F {0.3, 0.3});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    sfSprite_setScale(sprite, scale);
}

void display_hp(sfVector2f pos)
{
    char str[20] = {0};

    my_strcat(str, my_float_to_str(get_player()->hp, 1));
    my_strcat(str, " / ");
    my_strcat(str, my_float_to_str(get_player()->max_hpw, 1));
    sfText_setString(get_game()->text_chatbox, str);
    sfText_setPosition(get_game()->text_chatbox, pos);
    sfText_setColor(get_game()->text_chatbox, GREEN);
    sfRenderWindow_drawText(get_window()->window,
    get_game()->text_chatbox, NULL);
    stick_icon("hp", pos);
}

void display_stattt(sfVector2f pos, float stat, char *id, sfColor color)
{
    char str[20] = {0};

    my_strcat(str, my_float_to_str(stat, 1));
    sfText_setString(get_game()->text_chatbox, str);
    sfText_setPosition(get_game()->text_chatbox, pos);
    sfText_setColor(get_game()->text_chatbox, color);
    sfRenderWindow_drawText(get_window()->window,
    get_game()->text_chatbox, NULL);
    stick_icon(id, pos);
}

void display_globalstat(void)
{
    sfVector2f pos = {1920 / 2 - 14 * 2, 1080 / 2 + 18 * 2};

    sfText_setCharacterSize(get_game()->text_chatbox, 25);
    sfText_setScale(get_game()->text_chatbox, V2F {1, 1});
    display_hp(V2F {pos.x, pos.y - 180});
    display_stattt(V2F {pos.x, pos.y - 150},
    get_player()->max_attackw, "atk", RED);
    display_stattt(V2F {pos.x, pos.y - 120},
    get_player()->max_defensew, "def", BLUE);
    display_stattt(V2F {pos.x, pos.y - 90},
    get_player()->max_speedw, "speed", sfYellow);
}
