/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void def_up(sfText *text, float value)
{
    char str[10] = {0};

    str[0] = '+';
    my_strcat(str, my_float_to_str(value, 1));
    get_player()->defense += value;
    sfText_setColor(text, BLUE);
    sfText_setString(text, str);
    get_entity("levelup_sprite")->rect = get_stat_rect("def");
    sfSprite_setTextureRect(get_entity("levelup_sprite")->sprite,
    get_entity("levelup_sprite")->rect);
}
