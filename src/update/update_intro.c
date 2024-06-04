/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void move_it(int *to_move, int *to_move_y,
    int *offX_maX_miX_offY_maX_miY)
{
    (*to_move) += offX_maX_miX_offY_maX_miY[0];
    if ((*to_move) > offX_maX_miX_offY_maX_miY[1]) {
        (*to_move) = offX_maX_miX_offY_maX_miY[2];
        (*to_move_y) += offX_maX_miX_offY_maX_miY[3];
    }
    if ((*to_move_y) > offX_maX_miX_offY_maX_miY[4])
        (*to_move_y) = offX_maX_miX_offY_maX_miY[5];
}

void move_rect(entity_t *entity,
    int *offX_maX_miX_offY_maX_miY, ...)
{
    va_list list;
    int *to_move = NULL;
    int *to_move_y = NULL;
    float *clock = 0;
    float speed = 0;

    va_start(list, offX_maX_miX_offY_maX_miY);
    to_move = va_arg(list, int *);
    to_move_y = va_arg(list, int *);
    clock = va_arg(list, float *);
    speed = va_arg(list, double);
    for (; *clock > speed * 0.02; *clock -= speed * 0.02) {
        move_it(to_move, to_move_y, offX_maX_miX_offY_maX_miY);
        sfSprite_setTextureRect(entity->sprite, entity->rect);
    }
    va_end(list);
}

void update_intro(void)
{
    static float clock = 0;
    static float clock2 = 0;

    init_bg();
    init_bg2();
    if (!get_entity("sage"))
        init_sage();
    clock += get_window()->delay;
    clock2 += get_window()->delay;
    move_rect(get_entity("sage"),
    get_entity("sage")->offset_rect, &get_entity("sage")->rect.left,
    &get_entity("sage")->rect.top, &clock, 5.0);
    move_rect(get_entity("bg"),
    get_entity("bg")->offset_rect, &get_entity("bg")->rect.left,
    &get_entity("bg")->rect.top, &clock2, 1.0);
}
