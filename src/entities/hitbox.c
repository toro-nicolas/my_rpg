/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The hitbox.c
*/
/**
 * @file hitbox.c
 * @brief The hitbox.c
 * @author Nicolas TORO
 */

#include "csfml.h"

int is_hitbox_intersecting(sfRectangleShape *hitbox1,
    sfRectangleShape *hitbox2)
{
    sfFloatRect hitbox1_rect = sfRectangleShape_getGlobalBounds(hitbox1);
    sfFloatRect hitbox2_rect = sfRectangleShape_getGlobalBounds(hitbox2);

    return sfFloatRect_intersects(&hitbox1_rect, &hitbox2_rect, NULL);
}
