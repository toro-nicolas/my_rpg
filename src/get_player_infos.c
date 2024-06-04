/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

entity_t *get_player_entity(void)
{
    return get_game()->player;
}

player_t *get_player(void)
{
    return get_game()->player->entity_struct;
}

sfVector2f player_pos(void)
{
    return get_player_entity()->position;
}

sfVector2f player_dim(void)
{
    return (sfVector2f)
    {ABS((get_player_entity()->rect.width *
    get_player_entity()->scale.x)),
    ABS((get_player_entity()->rect.height *
    get_player_entity()->scale.y))};
}

sfVector2f player_dimo(void)
{
    return (sfVector2f)
    {ABS((get_player_entity()->rect.width / 2 *
    get_player_entity()->scale.x)),
    ABS((get_player_entity()->rect.height / 2 *
    get_player_entity()->scale.y))};
}
