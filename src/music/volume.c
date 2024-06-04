/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The volume.c
*/
/**
 * @file volume.c
 * @brief The volume.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void update_volume(void)
{
    sfMusic_setVolume(get_window()->music, get_window()->vol_music);
    sfMusic_setVolume(get_window()->fx, get_window()->vol_fx);
}
