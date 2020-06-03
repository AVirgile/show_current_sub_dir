/*
** Created on Wed Jun 03 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static void swap_data(file_list **list)
{
    char *tmp_name = (*list)->name;
    char *tmp_fullpath = (*list)->fullpath;
    bool tmp_dir = (*list)->is_dir;

    (*list)->name = (*list)->next->name;
    (*list)->fullpath = (*list)->next->fullpath;
    (*list)->is_dir = (*list)->next->is_dir;
    (*list)->next->name = tmp_name;
    (*list)->next->fullpath = tmp_fullpath;
    (*list)->next->is_dir = tmp_dir;
}

static void sort_alpha(file_list ***head)
{
    file_list *tmp = NULL;
    file_list *last = NULL;
    bool sort = false;

    do {
        sort = false;
        tmp = **head;
        while (tmp->next != last) {
            if (my_strcmpi(tmp->name, tmp->next->name) > 0) {
                sort = true;
                swap_data(&tmp);
            }
            tmp = tmp->next;
        }
        last = tmp;
    } while (sort == true);
}

static void sort_modif(file_list ***head)
{

}

int sort_list(file_list **head, global *stct)
{
    if (*head == NULL)
        return (0);
    if (stct->values->order == ALPHA)
        sort_alpha(&head);
    if (stct->values->order == MODIF)
        sort_modif(&head);
    return (0);
}