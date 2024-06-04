/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The vectors.c
*/
/**
 * @file vectors.c
 * @brief The vectors.c
 * @author Nicolas TORO
 */

#include "csfml.h"

float distance_heuristic(sfVector2f a, sfVector2f b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int vector_cmp(sfVector2f a, sfVector2f b)
{
    return (a.x == b.x && a.y == b.y);
}

sfVector2f vector_add(sfVector2f a, sfVector2f b)
{
    return (sfVector2f){a.x + b.x, a.y + b.y};
}

sfVector2f move_to_next_point(sfVector2f start, sfVector2f end,
    int speed, entity_t *entity)
{
    sfVector2f new_vector = start;

    end.y -= 32;
    speed *= 100;
    if (new_vector.x < end.x &&
    a_ov(RIGHT_M, (float)speed * get_window()->delay * 0.7071f, entity))
        new_vector.x += (float)speed * get_window()->delay * 0.7071f;
    if (new_vector.x > end.x &&
    a_ov(LEFT_M, (float)speed * get_window()->delay * 0.7071f, entity))
        new_vector.x -= (float)speed * get_window()->delay * 0.7071f;
    if (new_vector.y < end.y &&
    a_ov(DOWN_M, (float)speed * get_window()->delay * 0.7071f, entity))
        new_vector.y += (float)speed * get_window()->delay * 0.7071f;
    if (new_vector.y > end.y &&
    a_ov(TOP_M, (float)speed * get_window()->delay * 0.7071f, entity))
        new_vector.y -= (float)speed * get_window()->delay * 0.7071f;
    return new_vector;
}
