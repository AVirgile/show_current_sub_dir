/*
** Created on Wed Jun 03 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static void additional_info(file_list *file, global *stct)
{
    struct stat st = {0};
    time_t date = 0;
    char *result = NULL;

    stat(file->fullpath, &st);
    if (stct->values->list != NULL) {
    my_printf("[");
        for (opt_info *tmp = stct->values->list; tmp != NULL; tmp = tmp->next) {
            if (tmp->fileinfo == DATE) {
                date = st.st_mtime;
                result = ctime(&date);
                result[my_strlen(result) - 1] = 0;
                my_printf("%s", result);
            }
            if (tmp->fileinfo == SIZE) {
                my_printf("%d", st.st_size);
            }
            if (tmp->next != NULL)
                my_printf(" ");
        }
        my_printf("] ");
    }
}

static int dir_cases(file_list *tmp, global *stct, char *path, unsigned int intern)
{
    my_printf("\n");
    for (unsigned int i = 0; i < intern; i++)
        my_printf("  ");
    additional_info(tmp, stct);
    if (stct->values->print_full_path == true)
        my_printf("\e[0;34m%s\n\x1b[0m", tmp->fullpath);
    else
        my_printf("\e[0;34m%s\n\x1b[0m", tmp->name);
    if (scsd(stct, my_pathcat(path, tmp->name), intern + 1) == 84)
        return (84);
    return (0);
}

static void reg_cases(file_list *tmp, global *stct, unsigned int intern)
{
    for (unsigned int i = 0; i < intern; i++)
        my_printf("  ");
    additional_info(tmp, stct);
    if (stct->values->print_full_path == true)
        my_printf("%s\n", tmp->fullpath);
    else
        my_printf("%s\n", tmp->name);
}

int recurse_output(file_list *head, global *stct, char *path, unsigned int intern)
{
    for (file_list *tmp = head; tmp != NULL; tmp = tmp->next) {
        if (stct->values->show_hide == false && my_strncmp(".", tmp->name, 1) == 0)
            continue;
        if (tmp->is_dir == true) {
            if (dir_cases(tmp, stct, path, intern) == 84)
                return (84);
        }
        else if (stct->values->list_dir_only == false) {
            reg_cases(tmp, stct, intern);
        }
    }
    return (0);
}