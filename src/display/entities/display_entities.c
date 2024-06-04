/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void check_mob_alive(void)
{
    entity_t *entity = NULL;

    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        entity = tmp->data;
        if (entity->type == MOB &&
        ((mob_t *)entity->entity_struct)->animation.orientation == DISAPPEAR
        && ((mob_t *)entity->entity_struct)->animation.current >= 5)
            previous_to_next(&get_game()->entities_list, tmp);
    }
}

static int collect(entity_t **mob_e, mob_t **mob_t)
{
    sfSprite_setColor((*mob_e)->sprite, sfWhite);
    sfText_destroy((*mob_t)->text);
    (*mob_t)->text = NULL;
    (*mob_e)->hit_clock = 0;
    (*mob_t)->is_hit = 0;
    (*mob_t)->hp -=
    calculate_damage(get_player()->max_attackw, (*mob_t)->defense);
}

static int display_text(entity_t **mob_e, mob_t **mob_t)
{
    if (!(*mob_t)->text || (*mob_t)->text == NULL)
        (*mob_t)->text = create_text(4, "",
        get_font(), 50, sfWhite);
    sfText_setString((*mob_t)->text,
    my_float_to_str(
    calculate_damage(get_player()->attack, (*mob_t)->defense), 1));
    sfText_setPosition((*mob_t)->text,
    V2F {(*mob_e)->position.x + 50, (*mob_e)->position.y - 50});
    sfRenderWindow_drawText(get_window()->window, (*mob_t)->text, NULL);
    return 0;
}

static void get_hit(entity_t *entity)
{
    if (!(mob_t *)(entity->entity_struct)
    || !((mob_t *)(entity->entity_struct))->is_hit)
        return;
    if (((mob_t *)(entity->entity_struct))->is_hit == 1 &&
    ((mob_t *)(entity->entity_struct))->animation.orientation != DEAD
    && entity->hit_clock > 0.25) {
        play_sound(entity, ((mob_t *) (entity->entity_struct))->hit_sound);
        entity->hit_clock = 0;
        ((mob_t *)(entity->entity_struct))->is_hit = 2;
    }
    if (entity->hit_clock < 0.25 &&
    ((mob_t *)(entity->entity_struct))->animation.orientation != DEAD &&
    ((mob_t *)(entity->entity_struct))->animation.orientation != DISAPPEAR) {
        display_text(&entity, (mob_t **)&(entity->entity_struct));
        sfSprite_setColor(entity->sprite, sfRed);
    } else
        collect(&entity, (mob_t **)&(entity->entity_struct));
}

void display_entity(entity_t *entity)
{
    if (entity->type == MOB) {
        sfRenderWindow_drawSprite(get_window()->window,
        entity->sprite, NULL);
        get_hit(entity);
    }
    if (entity->type == MOB && get_user()->show_hitbox)
        sfRenderWindow_drawRectangleShape(get_window()->window,
        entity->hitbox, NULL);
    if (entity->type == ITEM)
        display_item(entity);
    if (entity->type == DECOR) {
        sfRenderWindow_drawSprite(get_window()->window,
        get_entity("ladder")->sprite, NULL);
        if (interact(get_entity("ladder")))
            restart_game();
    }
    if (entity->type == NPC)
        display_npc(entity);
}
