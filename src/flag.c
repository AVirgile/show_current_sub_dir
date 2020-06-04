/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

int decode_mask(short const mask, global *stct)
{
    if (mask & a_Flags)
        stct->values->show_hide = true;
    if (mask & d_Flags)
        stct->values->list_dir_only = true;
    if (mask & s_Flags)
        stct->values->fileinfo = SIZE;
    if (mask & f_Flags)
        stct->values->print_full_path = true;
    if (mask & D_Flags)
        stct->values->fileinfo = DATE;
    if (mask & t_Flags)
        stct->values->order = MODIF;
    return (0);
}