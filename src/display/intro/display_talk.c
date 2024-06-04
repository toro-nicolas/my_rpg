/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

char **intro_text(void)
{
    static char *text[] =
        {"Bonjour jeune villageois !",
        "Tu es choisi pour...",
        "sauver le monde de la \ndestruction !",
        "Choisis ton personnage...\net pars a l'aventure !",
        "Une fois choisi, \nle but est tres simple...",
        "Tu es coince dans un \nlabyrinthe et doit \ntrouver la sortie !",
        "Et ce sur autant \nd'etages que tu peux !",
        "La touche 'E' te permettra \nd'interagir avec les objets...",
        "La touche 'R' te permettra \nd'ouvrir ton inventaire...",
        "La touche 'A' te permettra \nd'attaquer les monstres...",
        "Pour choisir l'objet dans \nl'inventaire, "
        "utilise les \nnumeros de 1 a 3...",
        "Bonne chance !",
        NULL};

    return text;
}

void letter_by_letter(float *clock, char **str, int *j)
{
    if (*j == my_strlen(*str)) {
        *clock = 0;
        return;
    }
    for (; *clock > 0.05; *clock -= 0.05)
        (*j)++;
}

void text_moving(float *clock, int *i)
{
    char *str = NULL;
    char *str2 = NULL;
    static int j = 0;

    str = intro_text()[*i];
    letter_by_letter(clock, &str, &j);
    str2 = strndup(str, j);
    sfText_setString(get_game()->text_chatbox, str2);
    if (PASSKEYK) {
        (*i)++;
        j = 0;
        PASSKEYK = 0;
    }
}

void text_center_in_rect_with_pos(sfIntRect rect,
    sfVector2f pos, sfVector2f scale)
{
    sfVector2f text_pos = {0};
    sfFloatRect bounds = sfText_getGlobalBounds(get_game()->text_chatbox);

    text_pos.x = pos.x + (rect.width * scale.x / 2) - (bounds.width / 2);
    text_pos.y = pos.y + (rect.height * scale.y / 2) - (bounds.height / 2);
    text_pos.y -= 50;
    sfText_setPosition(get_game()->text_chatbox, text_pos);
}

int display_talk(char reset)
{
    static float clock = 0;
    static int i = 0;
    static int j = 0;

    i = reset ? 0 : i;
    j = reset ? 0 : j;
    if (!get_game()->text_chatbox)
        return 0;
    if (intro_text()[i] == NULL || get_entity("chatbox") == NULL)
        return 1;
    sfRenderWindow_drawSprite(get_window()->window,
    get_entity("chatbox")->sprite, NULL);
    sfRenderWindow_drawText(get_window()->window,
    get_game()->text_chatbox, NULL);
    clock += get_window()->delay;
    text_moving(&clock, &i);
    text_center_in_rect_with_pos(get_entity("chatbox")->rect,
    get_entity("chatbox")->position, get_entity("chatbox")->scale);
    return 0;
}
