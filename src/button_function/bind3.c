/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** menu.c
*/

#include "csfml.h"

void bind_slot2(void)
{
    get_bind()->binding = &(get_bind()->inv2);
}

void bind_slot3(void)
{
    get_bind()->binding = &(get_bind()->inv3);
}

void bind_inv(void)
{
    get_bind()->binding = &(get_bind()->inv);
}
