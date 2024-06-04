/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** menu.c
*/

#include "csfml.h"

void bind_down(void)
{
    get_bind()->binding = &(get_bind()->down);
}

void bind_attack(void)
{
    get_bind()->binding = &(get_bind()->attack);
}

void bind_pause(void)
{
    get_bind()->binding = &(get_bind()->pause);
}

void bind_interact(void)
{
    get_bind()->binding = &(get_bind()->interact);
}

void bind_slot1(void)
{
    get_bind()->binding = &(get_bind()->inv1);
}
