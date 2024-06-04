/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The mob_collisions.c
*/
/**
 * @file mob_collisions.c
 * @brief The mob_collisions.c
 * @author Nicolas TORO
 */

#include "csfml.h"

/*
int is_out_of_map(collision_e_t collision, sfVector2f add, sfVector2f vector)
{
    sfVector2f case_pos = pos_to_case(vector);
    sfVector2f case_pos_x = pos_to_case( V2F {vector.x + add.x, vector.y});
    sfVector2f case_pos_y = pos_to_case( V2F {vector.x, vector.y + add.y});
    int x = case_pos_x.x / CASE_SIZE;
    int y = case_pos_y.y / CASE_SIZE;
    int x_case = case_pos.x / CASE_SIZE;
    int y_case = case_pos.y / CASE_SIZE;

    if (vector.x + add.x < 0 || vector.y + add.y < 0)
        return 1;
    if ((collision == LEFT_M || collision == RIGHT_M) &&
    get_game()->map_infos->map[x + 1][y_case + 1] == EMPTY)
        return 1;
    if ((collision == TOP_M || collision == DOWN_M) &&
    get_game()->map_infos->map[x_case + 1][y + 1] == EMPTY)
        return 1;
    return 0;
}*/

sfVector2f get_collision_vector(sfVector2f fix, sfVector2f move)
{
    sfVector2f vector = {0, 0};
    float x = fix.x - move.x;
    float y = fix.y - move.y;
    float norm = sqrt(pow(x, 2) + pow(y, 2));

    if (norm == 0)
        return vector;
    vector.x = x / norm;
    vector.y = y / norm;
    return vector;
}

void knockback(entity_t *entity, entity_t *knockbacked_entity,
    float resistance)
{
    sfVector2f vector = get_collision_vector(
        entity->position, knockbacked_entity->position);
    sfVector2f hitbox_size =
        sfRectangleShape_getSize(knockbacked_entity->hitbox);
    int sign1 = (vector.x < 0) ? 1 : -1;
    int sign2 = (vector.y < 0) ? 1 : -1;

    hitbox_size.x = hitbox_size.x * knockbacked_entity->scale.x;
    hitbox_size.y = hitbox_size.y * knockbacked_entity->scale.y;
    for (int i = 0; i < 25 - (int)resistance; i++) {
        if (is_invalid_case(pos_to_case(V2F {knockbacked_entity->position.x -
        vector.x + sign1 * (hitbox_size.x / 4), (knockbacked_entity->position.y
        + (hitbox_size.y / 2))})) == 0)
            knockbacked_entity->move.x -= vector.x;
        if (is_invalid_case(pos_to_case(V2F {knockbacked_entity->position.x,
        (knockbacked_entity->position.y + (hitbox_size.y / 2)) - vector.y
        + sign2 * (hitbox_size.y / 2)})) == 0)
            knockbacked_entity->move.y -= vector.y;
    }
}

static void update_entity_pos(entity_t *entity1, entity_t *entity2)
{
    sfVector2f vector =
        get_collision_vector(entity1->position, entity2->position);
    int sign1 = (vector.x < 0) ? 1 : -1;
    int sign2 = (vector.y < 0) ? 1 : -1;
    sfVector2f hitbox_size = sfRectangleShape_getSize(entity1->hitbox);

    hitbox_size.x = hitbox_size.x * entity1->scale.x;
    hitbox_size.y = hitbox_size.y * entity1->scale.y;
    for (int i = 0; i <
    MAX(ABS((int)(vector.x * 100)), ABS((int)(vector.y * 100))); i++) {
        if (i < ABS((int)(vector.x * 100)) && (is_invalid_case(pos_to_case(V2F
        {entity1->position.x + (sign1) - sign1 * (hitbox_size.x),
        (entity1->position.y)})) == 0))
            entity1->move.x -= sign1 * 0.01f;
        if ((i < ABS((int)(vector.y * 100)) && is_invalid_case(pos_to_case(V2F
        {entity1->position.x,
        entity1->position.y + (sign2) - sign2 * (hitbox_size.y)})) == 0))
            entity1->move.y -= sign2 * 0.01f;
    }
}

void check_collision(entity_t *entity1, entity_t *entity2)
{
    sfFloatRect hitbox1 = sfSprite_getGlobalBounds(entity1->sprite);
    sfFloatRect hitbox2 = sfSprite_getGlobalBounds(entity2->sprite);
    sfVector2f origin1 = sfRectangleShape_getOrigin(entity1->hitbox);
    sfVector2f origin2 = sfRectangleShape_getOrigin(entity2->hitbox);

    hitbox1.left = entity1->position.x + origin1.x;
    hitbox1.top = entity1->position.y + origin1.y;
    hitbox1.width -= 80;
    hitbox1.height -= 80;
    hitbox2.left = entity2->position.x + origin2.x;
    hitbox2.top = entity2->position.y + origin2.y;
    hitbox2.width -= 80;
    hitbox2.height -= 80;
    if (sfFloatRect_intersects(&hitbox1, &hitbox2, NULL) == sfFalse)
        return;
    update_entity_pos(entity1, entity2);
    update_entity_pos(entity2, entity1);
}

sfVector2f get_valid_random_pos(void)
{
    sfVector2f pos = {-1, -1};
    int size = get_game()->map_infos->size - 1;

    while (is_invalid_case(pos)) {
        pos.x = RANDINT(0, size * CASE_SIZE);
        pos.y = RANDINT(0, size * CASE_SIZE);
        pos = pos_to_case(pos);
    }
    pos.y -= 32;
    return pos;
}
