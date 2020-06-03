/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static int add_to_list(char const *filepath, file_to_open **head)
{
    file_to_open *node = malloc(sizeof(file_to_open));
    file_to_open *tmp = *head;

    if (node == NULL) {
        my_werror("Error while allocating memory\n");
        return (84);
    }
    node->name = my_strdup(filepath);
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
        return (0);
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = node;
    return (0);
}

static bool is_it_a_directory(char const *potential)
{
    struct stat st = {0};

    if (stat(potential, &st) == -1)
        return (false);
    if (S_ISDIR(st.st_mode))
        return (true);
    return (false);
}

static short get_mask(char const *potOpt, short mask)
{
    bool find = false;

    for (int i = 1; potOpt[i]; i++) {
        find = false;
        for (int t = 0; table[t].opt != '\0'; t++) {
            if (table[t].opt == potOpt[i]) {
                mask |= table[t].byte;
                find = true;
            }
        }
        if (find == false) {
            write(2, &potOpt[i], 1);
            my_werror(": Error unknow flag\n");
            return (-1);
        }
    }
    return (mask);
}

static int get_opt(global *stct, char const *argv[])
{
    short mask = 0;

    for (int i = 1; argv[i]; i++) {
        if (argv[i][0] == '-') {
            mask = get_mask(argv[i], mask);
            if (mask == -1) return (84);
        } else if (is_it_a_directory(argv[i]) == true) {
            if (add_to_list(argv[i], &stct->list) == 84) return (84);
        } else {
            my_werror("Error Opening Dir [");
            my_werror(argv[i]);
            my_werror("]\n");
            return (84);
        }
    }
    if (decode_mask(mask, stct) == 84) return (84);
    return (0);
}

int main(__attribute__((unused)) int const argc, char const *argv[])
{
    global stct = {0};

    if (init_config(&stct) == 84)
        return (84);
    if (get_opt(&stct, argv) == 84)
        return (84);
    if (scsd(&stct, NULL) == 84)
        return (84);
    free_stct(&stct);
    return (0);
}
