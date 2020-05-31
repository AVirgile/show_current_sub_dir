/*
** EPITECH PROJECT, 2020
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../../include/libc.h"

static int count_size_of_lign(char *str, char spaces, char second)
{
    int i = 0;
    int j = 0;

    for (i = 0; str[i] == spaces || str[i] == second; i++);
    for (; str[i] != spaces && str[i] != second && str[i] != '\0'; i++)
        j++;
    return (j);
}

static int skip_spaces(char *str, char spaces, char second)
{
    int i = 0;

    for (; str[i] == spaces || str[i] == second; i++);
    for (; str[i] != spaces && str[i] != second && str[i] != '\0'; i++);
    return (i);
}

static char *fill(char *str, char *buffer, char spaces, char second)
{
    int i = 0;
    int j = 0;

    for (; str[i] == spaces || str[i] == second; i++);
    for (; str[i] != spaces && str[i] != second && str[i] != '\0'; i++, j++)
        buffer[j] = str[i];
    buffer[j] = '\0';
    return (buffer);
}

static int number_lign(char *str, char spaces, char second)
{
    int j = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != spaces && str[i] != second && (str[i + 1] == spaces ||
        str[i + 1] == second || str[i + 1] == '\0'))
            j++;
    }
    return (j);
}

char **my_str_to_word_array(char *str, char separators, char second)
{
    char **buffer = NULL;
    int i = 0;
    int nb_lign = number_lign(str, separators, second);

    buffer = malloc(sizeof(char *) * (nb_lign + 1));
    if (buffer == NULL)
        return (NULL);
    for (; i != nb_lign; i++) {
        buffer[i] = malloc(sizeof(char) * (count_size_of_lign(str,
        separators, second) + 1));
        if (buffer[i] == NULL)
            return (NULL);
        buffer[i] = fill(str, buffer[i], separators, second);
        str = str + skip_spaces(str, separators, second);
    }
    buffer[i] = NULL;
    return (buffer);
}