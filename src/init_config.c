/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

int init_config(global *stct)
{
    stct->values = malloc(sizeof(config));
    if (stct->values == NULL) {
        my_werror("Memory allocation failed\n");
        return(84);
    }
    stct->values->show_hide = false;
    stct->values->list_dir_only = false;
    stct->values->follow_symLink = false;
    stct->values->print_full_path = false;
    stct->values->tree_depth = NONE;
    stct->values->order = ALPHA;
    return (0);
}