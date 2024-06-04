/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The save_map.c
*/
/**
 * @file save_map.c
 * @brief The save_map.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void save_map(void)
{
    int fd = open("save/map", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    close(fd);
}
