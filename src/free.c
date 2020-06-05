/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static void free_file(file_to_open **head)
{
    file_to_open *prev = NULL;
    file_to_open *tmp = *head;

    while (tmp != NULL) {
        prev = tmp;
        tmp = tmp->next;
        free(prev->name);
        free(prev);
    }
    *head = NULL;
}

static void free_list_opt(opt_info **head)
{
    opt_info *prev = NULL;
    opt_info *tmp = *head;

    while (tmp != NULL) {
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    *head = NULL;
}

void free_file_list(file_list **head)
{
    file_list *prev = NULL;
    file_list *tmp = *head;

    while (tmp != NULL) {
        prev = tmp;
        tmp = tmp->next;
        free(prev->name);
        free(prev->fullpath);
        free(prev);
    }
    *head = NULL;
}

void free_stct(global *stct)
{
    free_file(&stct->list);
    free_list_opt(&stct->values->list);
    free(stct->values);
}