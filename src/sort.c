/*
** Created on Wed Jun 03 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static void sort_alpha(file_list ***head)
{

}

static void sort_modif(file_list ***head)
{
    
}

int sort_list(file_list **head, global *stct)
{
    if (stct->values->order == ALPHA) {
        sort_alpha(&head);
    }
    if (stct->values->order == MODIF) {
        sort_modif(&head);
    }
    return (0);
}