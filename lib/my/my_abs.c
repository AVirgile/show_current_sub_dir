/*
** EPITECH PROJECT, 2019
** my_libC
** File description:
** my_libC
*/

#include "../../include/libc.h"

int my_abs(int j)
{
    if (j < 0) {
        j *= -1;
        return (j);
    }
    return (j);
}