/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** random npc
*/

#include "csfml.h"


static void scepter_stat1(item_t *item, int floor)
{
    item->defense = RANDINT(1, 5) *
        (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->attack = RANDINT(2, 10) *
        (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->speed = 0;
    item->hp = RANDINT(10, 40) *
        (1 * log(floor + 1)) * pow(1.05, floor);
}

static void dagger_stat1(item_t *item, int floor)
{
    item->defense = RANDINT(1, 5) *
        (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->attack = RANDINT(20, 50) *
        (1 + 0.3 * log(floor + 1)) * pow(1.05, floor);
    item->speed = 0;
    item->hp = RANDINT(10, 20) *
        (1 * 0.5 * log(floor + 1)) * pow(1.05, floor);
}

static void lance_stat1(item_t *item, int floor)
{
    item->defense = RANDINT(1, 5) *
        (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->attack = RANDINT(10, 30) *
        (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->speed = 0;
    item->hp = RANDINT(10, 20) *
        (1 * 0.5 * log(floor + 1)) * pow(1.05, floor);
}

static char **drop_item_dialog(void)
{
    static char *dialog[] = {
        "J'ai cru comprendre \nque tu galeres !",
        "J'ai un cadeau pour toi !",
        "surtout ne le dis \npas au sage...",
        "Il ne voudrait pas \nque je t'aide...",
        "Il est gentil, mais...",
        "il y a encore plein\n de secrets que tu ignores...",
        "Bonne chance !",
        NULL};

    return dialog;
}

static int drop_item2(sfVector2f pos)
{
    entity_t *item = RANDOM_ITEM(pos);

    item->position = pos;
    ((item_t *) item->entity_struct)->on_ground = 1;
    ((item_t *) item->entity_struct)->speed = 0;
    if (strncmp(item->id, "s", 1) == 0)
        scepter_stat1(item->entity_struct, get_game()->map_infos->floor);
    if (strncmp(item->id, "d", 1) == 0)
        dagger_stat1(item->entity_struct, get_game()->map_infos->floor);
    if (strncmp(item->id, "l", 1) == 0)
        lance_stat1(item->entity_struct, get_game()->map_infos->floor);
    return 0;
}

int remove_me(entity_t *self)
{
    for (nodes_t *node = get_game()->entities_list; node; node = node->next) {
        if ((entity_t *)node->data == self) {
            previous_to_next(&get_game()->entities_list, node);
            return 1;
        }
    }
    return 0;
}

//int end_animation(sfVector2f pos)
//{
//    static sfSprite *sprite = NULL;
//    static sfClock *clock = NULL;
//    static entity_t *entity = NULL;
//    static int choice = 0;
//    sfIntRect rect = {0, 3640, 200, 200};
//    int sprite_au_pif[] = {3640, 3840, 4040, 4240};
//    int offset[] = {200, 1400, 0, 200, rect.top, rect.top};
//    static int ok = 0;
//
//    if (!ok) {
//        choice = rand() % 4;
//        ok = 1;
//    }
//    if (!sprite) {
//        rect.top = sprite_au_pif[choice];
//        offset[4] = sprite_au_pif[choice];
//        offset[5] = sprite_au_pif[choice];
//        sprite = create_sprite(5, get_game()->main_texture, rect, pos,
//        V2F {100, 100}, V2F {1, 1});
//        entity = create_entity(3, CUSTOM, "bite", sprite);
//        clock = sfClock_create();
//    }
//    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
//    move_rect(entity, offset, &entity->rect.left,
//    &entity->rect.top, &clock, 12.0);
//    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
//    if (entity->rect.left >= offset[1]) {
//        ok = 0;
//        return 1;
//    }
//    return 0;
//}
int drop_itemnpc(entity_t *self)
{
    sfFloatRect npc_r =
            sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
            sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(drop_item_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    if (display_chatnpc(drop_item_dialog(), self->position, 0)) {
        drop_item2(self->position);
        remove_me(self);
        return 1;
    }
    return 0;
}
