/*
** EPITECH PROJECT, 2019
** my_libC
** File description:
** my_libC
*/

#include "../../include/libc.h"

int my_isxdigit(int c)
{
    if (((char) c >= '0' && (char) c <= '9')
        || ((char) c >= 'a' && (char) c <= 'f')
        || ((char) c >= 'A' && (char) c <= 'F'))
        return (1);
    return (0);
}