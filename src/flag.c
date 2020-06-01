/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

int decode_mask(short const mask, global *stct)
{
    if (mask & a_Flags) {
        my_printf("flag -> a\n");
    }
    if (mask & d_Flags) {
        my_printf("flag -> d\n");
    }
    if (mask & l_Flags) {
        my_printf("flag -> l\n");
    }
    if (mask & f_Flags) {
        my_printf("flag -> f\n");
    }
    if (mask & L_Flags) {
        my_printf("flag -> L\n");
    }
    if (mask & t_Flags) {
        my_printf("flag -> t\n");
    }
    return (0);
}