/*
** EPITECH PROJECT, 2019
** my_libC_template
** File description:
** my_libC_template
*/

#include "../../include/libc.h"
#include <unistd.h>

void my_werror(char const *message)
{
    write(2, message, my_strlen(message));
}