/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void display_stat(entity_t *entity)
{
    if (entity->type == PLAYER)
        display_player_stat(entity);
}
