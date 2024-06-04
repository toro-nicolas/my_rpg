/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The super_push.c
*/
/**
 * @file super_push.c
 * @brief The super_push.c
 * @author Nicolas TORO
 */

#include "mylist.h"

void super_push_f(nodes_t **head, void *data, type_t type)
{
    nodes_t *new = malloc(sizeof(nodes_t));

    new->data = data;
    new->type = type;
    new->previous = NULL;
    new->next = *head;
    if (*head != NULL)
        (*head)->previous = new;
    *head = new;
    return;
}

void super_push_b(nodes_t **head, void *data, type_t type)
{
    nodes_t *new = malloc(sizeof(nodes_t));
    nodes_t *tmp;

    if (*head == NULL) {
        new->data = data;
        new->type = type;
        new->previous = NULL;
        new->next = NULL;
        *head = new;
        return;
    }
    for (tmp = *head; tmp->next != NULL; tmp = tmp->next);
    new->data = data;
    new->type = type;
    new->previous = tmp;
    new->next = NULL;
    tmp->next = new;
}
