/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

static void offset2(char *action, int *offset_rect, sfIntRect rect)
{
    if (strcmp(action, "die") == 0) {
        offset_rect[1] = rect.left + (32 * 7);
        offset_rect[4] += rect.top + (32 * 7);
        offset_rect[5] += rect.top + (32 * 7);
    }
}

void choose_offset(char *action, int *offset_rect, sfIntRect rect)
{
    if (strcmp(action, "idle") == 0) {
        offset_rect[1] = rect.left + 32;
        offset_rect[4] = rect.top;
        offset_rect[5] = rect.top;
    }
    if (strcmp(action, "walk") == 0) {
        offset_rect[1] = rect.left + (32 * 7);
        offset_rect[4] += rect.top + (32 * 3);
        offset_rect[5] += rect.top + (32 * 3);
    }
    if (strcmp(action, "attack") == 0) {
        offset_rect[1] = rect.left + (32 * 7);
        offset_rect[4] += rect.top + (32 * 8);
        offset_rect[5] += rect.top + (32 * 8);
    }
    offset2(action, offset_rect, rect);
}

static sfFloatRect get_hitbox_collider(entity_t *entity)
{
    float x = entity->position.x;
    float y = entity->position.y + ABS(entity->rect.height / 2
    * entity->scale.y);
    sfFloatRect hitbox = {x - 20, y - 10, 40, 18};

    return hitbox;
}

static int check_left_right(sfImage *map, int side, sfFloatRect hitbox)
{
    int count = 0;

    for (int x = 0; x <= hitbox.width; x += hitbox.width / 5) {
        if (sfColor_toInteger(sfImage_getPixel(map, hitbox.left + x,
        side == DOWN_M ? hitbox.top + hitbox.height : hitbox.top)) ==
        sfColor_toInteger(sfRed))
            count++;
    }
    if (count >= 2)
        return 0;
    return 1;
}

static int check_top_down(sfImage *map, int side, sfFloatRect hitbox)
{
    int count = 0;

    for (int y = 0; y <= hitbox.height; y += hitbox.height / 5) {
        if (sfColor_toInteger(sfImage_getPixel(map, side == LEFT_M ?
        hitbox.left : hitbox.left + hitbox.width, hitbox.top + y)) ==
        sfColor_toInteger(sfRed))
            count++;
    }
    if (count >= 2)
        return 0;
    return 1;
}

static void change_hitbox(int side, sfFloatRect *hitbox, float speed)
{
    if (side == LEFT_M)
        hitbox->left -= speed;
    if (side == TOP_M)
        hitbox->top -= speed;
    if (side == RIGHT_M)
        hitbox->left += speed;
    if (side == DOWN_M)
        hitbox->top += speed;
}

int a_ov(int side, float speed, entity_t *entity)
{
    sfFloatRect hitbox = get_hitbox_collider(entity);
    sfImage *map = get_game()->map_infos->color_map;
    sfVector2u map_size = sfImage_getSize(map);

    change_hitbox(side, &hitbox, speed);
    if (hitbox.left < 0 || hitbox.top < 0 ||
    hitbox.left + hitbox.width > map_size.x ||
    hitbox.top + hitbox.height > map_size.y)
        return 0;
    if (side == TOP_M || side == DOWN_M)
        if (!check_left_right(map, side, hitbox))
            return 0;
    if (side == RIGHT_M || side == LEFT_M)
        if (!check_top_down(map, side, hitbox))
            return 0;
    return 1;
}

void move_player(entity_t *player)
{
    float speed = get_player()->speed;
    sfVector2f move = {0, 0};

    if (LEFTK && a_ov(LEFT_M, speed * get_window()->delay * 0.7071f, player))
        move.x -= speed;
    if (RIGHTK && a_ov(RIGHT_M, speed * get_window()->delay * 0.7071f, player))
        move.x += speed;
    if (UPK && a_ov(TOP_M, speed * get_window()->delay * 0.7071f, player))
        move.y -= speed;
    if (DOWNK && a_ov(DOWN_M, speed * get_window()->delay * 0.7071f, player))
        move.y += speed;
    move.x *= (get_window()->delay * 0.7071f);
    move.y *= (get_window()->delay * 0.7071f);
    player->position.x += move.x;
    player->position.y += move.y;
    sfSprite_move(player->sprite, move);
}

void update_player(void)
{
    float value = 8.0f;

    if (get_player()->hp <= 0)
        get_player()->hp = 0;
    if (get_player()->orientation == ATK) {
        value = 2.5f;
        if (get_player_entity()->rect.left
        == get_player_entity()->offset_rect[1]) {
            get_player()->is_attacking = 1;
            get_player()->orientation = NONE;
        }
    }
    move_rect(get_player_entity(), get_player_entity()->offset_rect,
        &get_player_entity()->rect.left, &get_player_entity()->rect.top,
        &get_player_entity()->clock, value);
    if (get_player()->hp > 0)
        move_player(get_player_entity());
    update_entity(get_player_entity());
    update_player2();
}
