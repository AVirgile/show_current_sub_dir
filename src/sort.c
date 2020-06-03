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

static int check_modification(char const *file_one, char const *file_two)
{
    struct stat st = {0};
    time_t time_one = {0};
    time_t time_two = {0};
     

    if (stat(file_one, &st) == -1) {
        my_werror("Error in stat call\n");
        return (84);
    }
    time_one = st.st_mtime;
    if (stat(file_two, &st) == -1) {
        my_werror("Error in stat call\n");
        return (84);
    }
    time_two = st.st_mtime;
    if (time_one > time_two)
        return (-1);
    return (0);
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

static int sort_modif(file_list ***head)
{
    file_list *tmp = NULL;
    file_list *last = NULL;
    bool sort = false;
    int ret = 0;

    do {
        sort = false;
        tmp = **head;
        while (tmp->next != last) {
            ret = check_modification(tmp->fullpath, tmp->next->fullpath);
            if (ret == 84)
                return (84);
            if (ret == -1) {
                sort = true;
                swap_data(&tmp);
            }
            tmp = tmp->next;
        }
        last = tmp;
    } while (sort == true);
    return (0);
}

int sort_list(file_list **head, global *stct)
{
    if (*head == NULL)
        return (0);
    sort_alpha(&head);
    if (stct->values->order == MODIF)
        if (sort_modif(&head) == 84)
            return (84);
    return (0);
}