/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"
#include <stdio.h>

static void update_player_xp(player_t *player)
{
    while (player->xp >= player->xp_to_next_level) {
        player->xp -= player->xp_to_next_level;
        player->level++;
        player->xp_to_next_level = player->level * 10;
    }
}

void get_ratio_xp(sfRectangleShape **current_xp,
    sfRectangleShape **max_bar_size)
{
    sfVector2f size = sfRectangleShape_getSize(*max_bar_size);
    double xp = (double)get_player()->xp /
        (double)get_player()->xp_to_next_level;
    float ratio = xp * size.x;

    sfRectangleShape_setSize(*current_xp, V2F {ratio, size.y});
}

void init_levelbar2(sfRectangleShape **levelbar,
    sfRectangleShape **current_xp, sfText **text)
{
    *levelbar = create_rectangle(7, V2F {900, BAR_SIZEH},
        V2F {1920 / 2, 1080 - 150},
        V2F {900 / 2, BAR_SIZEH / 2},
        V2F {1, 1}, sfTransparent, BLUE, 2);
    *current_xp = create_rectangle(7, V2F {900, BAR_SIZEH},
        V2F {1920 / 2, 1080 - 150},
        V2F {900 / 2, BAR_SIZEH / 2},
        V2F {1, 1}, BLUE, sfBlue, 2);
    *text = create_text(5, "", get_font(), 45, BLUE);
}

static void suitelevel(sfRectangleShape *levelbar,
    sfRectangleShape *current_xp, sfText *text, sfVector2f pos)
{
    sfRectangleShape_setPosition(levelbar, pos);
    sfRectangleShape_setPosition(current_xp, pos);
    sfText_setPosition(text, V2F {pos.x + 475, pos.y + 20});
    get_ratio_xp(&current_xp, &levelbar);
    sfRenderWindow_drawRectangleShape(get_window()->window, levelbar, NULL);
    sfRenderWindow_drawRectangleShape(get_window()->window, current_xp, NULL);
}

void display_levelbar(player_t *player)
{
    static sfRectangleShape *levelbar = NULL;
    static sfRectangleShape *current_xp = NULL;
    static sfText *text = NULL;
    char str[10] = {0};
    sfVector2f pos = V2F {1920 / 2, 1080 - 125};

    if (!levelbar)
        init_levelbar2(&levelbar, &current_xp, &text);
    update_player_xp(player);
    suitelevel(levelbar, current_xp, text, pos);
    my_strcat(str, "lvl \n");
    if (player->level < 10)
        my_strcat(str, "0");
    my_strcat(str, my_str_nbr(player->level));
    sfText_setString(text, str);
    sfRenderWindow_drawText(get_window()->window, text, NULL);
}
