/*
** EPITECH PROJECT, 2023
** Interaction
** File description:
** Interaction
*/

#include "csfml.h"

void create_key_i(entity_t **key)
{
    sfSprite *sprite = NULL;
    sfIntRect rect = get_stat_rect("pressE");
    sfVector2f pos = V2F {0, 0};
    sfVector2f scale = V2F {0.2, 0.2};

    sprite = create_sprite(5, get_game()->main_texture,
    rect, pos, V2F {200, 200}, scale);
    *key = create_entity(5, DECOR, "pressE", sprite, NULL, NULL);
    (*key)->offset_rect = MALLOC(sizeof(int) * 6);
    (*key)->offset_rect[0] = 400;
    (*key)->offset_rect[1] = 2178 + 400;
    (*key)->offset_rect[2] = 2178;
    (*key)->offset_rect[3] = 0;
    (*key)->offset_rect[4] = 2559;
    (*key)->offset_rect[5] = 2559;
}

int suitesuite(entity_t *key, sfFloatRect bounds2,
    entity_t *self, float *clock)
{
    sfVector2f self_pos = sfSprite_getPosition(self->sprite);
    int s = sfSprite_getScale(self->sprite).x < 0 ? -1 : 1;

    sfSprite_setPosition(key->sprite,
    V2F {self_pos.x + (bounds2.width / 2) * s, self_pos.y - 50});
    sfRenderWindow_drawSprite(get_window()->window, key->sprite, NULL);
    move_rect(key, key->offset_rect,
    &key->rect.left, &key->rect.top, clock, 70.0f);
    if (INTERACTK) {
        INTERACTK = 0;
        return 1;
    }
    return 0;
}

int interact(entity_t *self)
{
    static entity_t *key = NULL;
    static float clock = 0;
    sfFloatRect bounds = sfSprite_getGlobalBounds(get_player_entity()->sprite);
    sfFloatRect bounds2 = sfSprite_getGlobalBounds(self->sprite);

    if (!sfFloatRect_intersects(&bounds, &bounds2, NULL))
        return 0;
    if (key == NULL)
        create_key_i(&key);
    clock += get_window()->delay;
    return suitesuite(key, bounds2, self, &clock);
}
