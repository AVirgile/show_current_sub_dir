/*
** EPITECH PROJECT, 2019
** my_libC
** File description:
** my_libC
*/

#include "../../include/libc.h"

int my_isprint(int c)
{
    if ((char) c >= 32 && (char) c <= 126)
        return (1);
    return (0);
}