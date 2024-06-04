/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The damage.c
*/
/**
 * @file damage.c
 * @brief The damage.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void play_sound(entity_t *entity, char *path)
{
    sfMusic **sound = NULL;

    if (path == NULL)
        return;
    if (entity == NULL)
        sound = &get_window()->fx;
    else
        sound = &entity->sound;
    if (*sound != NULL)
        sfMusic_destroy(*sound);
    *sound = sfMusic_createFromFile(path);
    sfMusic_setVolume(*sound, get_window()->vol_fx);
    sfMusic_play(*sound);
}

void play_music(char *path)
{
    if (path == NULL)
        return;
    if (get_window()->music != NULL)
        sfMusic_destroy(get_window()->music);
    get_window()->music = sfMusic_createFromFile(path);
    sfMusic_setVolume(get_window()->music, get_window()->vol_music);
    sfMusic_setLoop(get_window()->music, sfTrue);
    sfMusic_play(get_window()->music);
}
