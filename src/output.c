/*
** Created on Wed Jun 03 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

int recurse_output(file_list *head, global *stct, char *path)
{
    for (file_list *tmp = head; tmp != NULL; tmp = tmp->next) {
        if (tmp->is_dir == true) {
            my_printf("\n_%s\n", tmp->name);
            if (scsd(stct, my_pathcat(path, tmp->name)) == 84)
                return (84);
        }
        else
            my_printf("___%s\n", tmp->name);
    }
    my_printf("\n");
    return (0);
}