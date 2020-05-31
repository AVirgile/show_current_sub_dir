/*
** EPITECH PROJECT, 2019
** CPool
** File description:
** my_memset
*/

#include "../../include/libc.h"

char *my_memset(char *a, char b, size_t size)
{
    size_t i = 0;

    while (i < size)
        a[i++] = b;
    return (a);
}