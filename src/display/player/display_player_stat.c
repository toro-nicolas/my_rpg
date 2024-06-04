/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void get_ratio_life(sfRectangleShape *lifebar, sfRectangleShape **current_life)
{
    sfVector2f size = sfRectangleShape_getSize(lifebar);
    float ratio = get_player()->hp / get_player()->max_hpw;

    if (ratio < 0)
        ratio = 0;
    if (ratio > 1)
        ratio = 1;
    sfRectangleShape_setSize(*current_life, V2F {size.x * ratio, size.y});
}

void init_lifebar(sfRectangleShape **lifebar, sfRectangleShape **current_life,
    sfSprite **sprite)
{
    *lifebar = create_rectangle(7,
        V2F {PLAYER_DIM.x, BAR_SIZEH},
        V2F {PLAYER_POS.x, PLAYER_POS.y - PLAYER_DIMO.y},
        V2F {PLAYER_DIMO.x, BAR_SIZEH / 2},
        V2F {1, 1}, sfTransparent, RED, 2);
    *current_life = create_rectangle(5,
        V2F {PLAYER_DIM.x, BAR_SIZEH},
        V2F {PLAYER_POS.x, PLAYER_POS.y - PLAYER_DIMO.y},
        V2F {PLAYER_DIMO.x, BAR_SIZEH / 2},
        V2F {1, 1}, RED);
    *sprite = create_sprite(2,
    get_game()->main_texture, get_stat_rect("life"));
    sfSprite_setOrigin(*sprite,
    V2F {get_stat_rect("life").width / 2,
            get_stat_rect("life").height / 2});
    sfSprite_setScale(*sprite, V2F {0.3, 0.3});
}

static void resize_if_needed(sfText *text, sfRectangleShape *lifebar)
{
    sfFloatRect rect_text = sfText_getGlobalBounds(text);
    sfVector2f size = sfRectangleShape_getSize(lifebar);

    while (sfText_getPosition(text).x + rect_text.width >
    sfRectangleShape_getPosition(lifebar).x + size.x / 2)
        sfText_move(text, V2F {-1, 0});
}

void display_numbers(sfVector2f pos, sfRectangleShape *lifebar)
{
    char str[20] = {0};

    my_strcat(str, my_float_to_str(get_player()->hp, 1));
    my_strcat(str, " / ");
    my_strcat(str, my_float_to_str(get_player()->max_hpw, 1));
    sfText_setCharacterSize(get_game()->text_chatbox, 20);
    sfText_setString(get_game()->text_chatbox, str);
    sfText_setPosition(get_game()->text_chatbox, pos);
    resize_if_needed(get_game()->text_chatbox, lifebar);
    sfText_setColor(get_game()->text_chatbox, sfRed);
    sfRenderWindow_drawText(get_window()->window,
    get_game()->text_chatbox, NULL);
}

void display_player_stat(entity_t *player_e)
{
    static sfRectangleShape *lifebar = NULL;
    static sfRectangleShape *current_life = NULL;
    static sfSprite *sprite = NULL;
    sfVector2f pos = V2F {PLAYER_POS.x, PLAYER_POS.y - PLAYER_DIMO.y};

    if (!lifebar)
        init_lifebar(&lifebar, &current_life, &sprite);
    sfRectangleShape_setPosition(lifebar, pos);
    sfRectangleShape_setPosition(current_life, pos);
    sfSprite_setPosition(sprite, V2F {pos.x - PLAYER_DIMO.x, pos.y});
    get_ratio_life(lifebar, &current_life);
    sfRenderWindow_drawRectangleShape(get_window()->window, lifebar, NULL);
    sfRenderWindow_drawRectangleShape(get_window()->window,
    current_life, NULL);
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    display_numbers(V2F {pos.x, pos.y - 30}, lifebar);
}
