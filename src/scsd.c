/*
** Created on Tue Jun 02 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

char *my_pathcat(char *dest, char *src)
{
    size_t l_one = my_strlen(dest) + 1;
    size_t l_two = my_strlen(src);
    size_t l_three = l_one + l_two + 1;
    char *result = malloc(l_three);

    if (result == NULL)
        return (NULL);
    for (l_one = 0; dest != NULL && dest[l_one] != '\0'; l_one++)
        result[l_one] = dest[l_one];
    result[l_one] = '/';
    for (l_two = 0; src != NULL && src[l_two] != '\0'; l_two++, l_one++)
        result[l_one + 1] = src[l_two];
    result[l_one + 1] = '\0';
    return (result);
}

static bool path_dir(char *path, char *name)
{
    char *tmp = my_pathcat(path, name);
    struct stat st;

    if (stat(tmp, &st) == -1) {
        my_werror("Debug: Error in stat\n");
        free(tmp);
        return (false);
    }
    if (S_ISDIR(st.st_mode)) {
        free(tmp);
        return (true);
    }
    free(tmp);
    return (false);
}

static int append(char *filename, file_list ***head, char *path, bool dir)
{
    file_list *node = malloc(sizeof(file_list));
    file_list *tmp = **head;

    if (node == NULL) {
        my_werror("Error while allocating memory\n");
        return (84);
    }
    node->name = my_strdup(filename);
    node->fullpath = my_pathcat(path, filename);
    if (dir == true)
        node->is_dir = true;
    else
        node->is_dir = false;
    node->next = NULL;
    if (**head == NULL) {
        **head = node;
        return (0);
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = node;
    return (0);
}

static int open_directory(dir_var *tools, char *path, global *stct, file_list **head)
{
    while ((tools->dp = readdir(tools->ptr)) != NULL) {
        if (my_strcmp(".", tools->dp->d_name) != 0 && my_strcmp("..", tools->dp->d_name) != 0) {
            if (path_dir(path, tools->dp->d_name) == true) {
                if (append(tools->dp->d_name, &head, path, true) == 84) return (84);
            } else {
                if (append(tools->dp->d_name, &head, path, false) == 84) return (84);
            }
        }
    }
    return (0);
}

int scsd(global *stct, char *path)
{
    dir_var tools = {0};
    file_list *head = NULL;
    
    if (path == NULL) {
        my_printf(".\n");
        path = getcwd(path, 0);
    }
    if (path == NULL) {
        my_werror("Error while gathering wording dir\n");
        return (84);
    }
    tools.ptr = opendir(path);
    if (tools.ptr == NULL) {
        my_werror("Error while opening dir\n");
        return (84);
    }
    if (open_directory(&tools, path, stct, &head) == 84)
        return (84);
    if (sort_list(&head, stct) == 84)
        return (84);
    if (recurse_output(head, stct, path) == 84)
        return (84);
    free_file_list(&head);
    closedir(tools.ptr);
    free(path);
    return (0);
}