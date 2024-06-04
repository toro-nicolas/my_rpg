/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"



void display_intro(void)
{
    sfRenderWindow_drawSprite(get_window()->window,
    get_entity("bg")->sprite, NULL);
    sfRenderWindow_drawSprite(get_window()->window,
    get_entity("sage")->sprite, NULL);
    if (display_talk(0))
        display_bonus();
}
