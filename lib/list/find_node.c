/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The find_node.c
*/
/**
 * @file find_node.c
 * @brief The find_node.c
 * @author Nicolas TORO
 */

#include "mylist.h"

nodes_t *my_find_node(nodes_t const *begin, void const *data_ref,
    int (*cmp) ())
{
    for (nodes_t *tmp = (nodes_t *)begin; tmp != NULL; tmp = tmp->next) {
        if ((cmp == NULL && tmp->data == data_ref)
        || (cmp != NULL && cmp(tmp->data, data_ref) == 0))
            return tmp;
    }
    return NULL;
}
