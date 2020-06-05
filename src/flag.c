/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static int add_to_list(opt_info **head, info value)
{
    opt_info *node = malloc(sizeof(file_list));
    opt_info *tmp = *head;

    if (node == NULL) {
        my_werror("Error while allocating memory\n");
        return (84);
    }
    node->fileinfo = value;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
        return (0);
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = node;
    return (0);
}

int decode_mask(short const mask, global *stct)
{
    if (mask & a_Flags)
        stct->values->show_hide = true;
    if (mask & d_Flags)
        stct->values->list_dir_only = true;
    if (mask & s_Flags)
        add_to_list(&stct->values->list, SIZE);
    if (mask & f_Flags)
        stct->values->print_full_path = true;
    if (mask & D_Flags)
        add_to_list(&stct->values->list, DATE);
    if (mask & t_Flags)
        stct->values->order = MODIF;
    return (0);
}