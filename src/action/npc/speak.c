/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** random npc
*/

#include "csfml.h"

char **speak_too_much_dialog(void)
{
    static char *dialog[] = {
        "Ah, j'ai plein de chose \na te dire !",
        "je t'ai raconte la fois \nou j'ai...",
        "rencontre un dragon ?",
        "Ah non, c'etait un chat...",
        "En fait je ne sais plus...",
        "Je t'ai deja parle de \nma soeur ?",
        "Elle est tres gentille \ntu sais...",
        "Elle a un chat...",
        "Ah non, c'etait un \ndragon...",
        "Enfin bref, \nbonne chance !",
        NULL};

    return dialog;
}

int suite_chat(char *current_phrase, int *j, sfVector2f pos, float *clock)
{
    char *str = my_strdup(current_phrase);
    char *str2 = NULL;
    static sfRectangleShape *rect = NULL;

    if (!rect) {
        rect = create_rectangle(7, V2F {250, 50},
        V2F {0, 0}, V2F {0, 0}, V2F {1, 1}, sfWhite, sfBlack, 2);
    }
    letter_by_letter(clock, &str, j);
    str2 = strndup(str, *j);
    sfText_setCharacterSize(get_game()->text_chatbox, 20);
    sfText_setPosition(get_game()->text_chatbox,
    V2F {pos.x + 50, pos.y - 100});
    sfRectangleShape_setPosition(rect, V2F {pos.x + 40, pos.y - 100});
    sfText_setColor(get_game()->text_chatbox, sfBlack);
    sfText_setString(get_game()->text_chatbox, str2);
    sfRenderWindow_drawRectangleShape(get_window()->window, rect, NULL);
    sfRenderWindow_drawText(get_window()->window,
    get_game()->text_chatbox, NULL);
}

int display_chatnpc(char **dialog, sfVector2f pos, int reset)
{
    static int i = 0;
    static int j = 0;
    static float clock = 0;

    if (dialog[i] == NULL || reset) {
        j = 0;
        i = 0;
        clock = reset ? 0 : clock;
        return reset ? 0 : 1;
    }
    clock += get_window()->delay;
    suite_chat(dialog[i], &j, pos, &clock);
    if (PASSKEYK) {
        i++;
        j = 0;
        PASSKEYK = 0;
    }
    return 0;
}

int speak(entity_t *self)
{
    sfFloatRect npc_r =
    sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
    sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(speak_too_much_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    return display_chatnpc(speak_too_much_dialog(), self->position, 0);
}
