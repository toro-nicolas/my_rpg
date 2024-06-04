/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The save_entities.c
*/
/**
 * @file save_entities.c
 * @brief The save_entities.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void save_entities(void)
{
    int fd = open("save/entities", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    close(fd);
}
