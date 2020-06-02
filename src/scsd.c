/*
** Created on Tue Jun 02 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#include "scsd.h"

static char *my_pathcat(char *dest, char *src)
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

static void recurse(struct dirent *dp, DIR *ptr, char *path, global *stct)
{
    while ((dp = readdir(ptr)) != NULL) {
        if (my_strcmp(".", dp->d_name) != 0 && my_strcmp("..", dp->d_name) != 0) {
            if (path_dir(path, dp->d_name) == true) {
                my_printf("_%s\n", dp->d_name);
                // mettre dans une liste chainée directory pour trier et faire l'output
                // Etudier les listes chainée pour quelle soit complémentaire au options
                // deux champs dedans le nom et le path complet impératif de mettre ca oublie pas
                // ou je péte un cable
                scsd(stct, my_pathcat(path, dp->d_name));
            } else {
                my_printf("___%s\n", dp->d_name);
                // mettre dans une liste chainée standard pour trier et faire l'output
                // Etudier les listes chainée pour quelle soit complémentaire au options
                // deux champs dedans le nom et le path complet impératif de mettre ca oublie pas
                // ou je péte un cable
            }
        }
    }
}

int scsd(global *stct, char *path)
{
    DIR *ptr = NULL;
    struct dirent *dp = NULL;
    
    if (path == NULL) {
        my_printf(".\n");
        path = getcwd(path, 0);
    }
    if (path == NULL) {
        my_werror("Error while gathering wording dir\n");
        return (84);
    }
    ptr = opendir(path);
    if (ptr == NULL) {
        my_werror("Error while opening dir\n");
        return (84);
    }
    recurse(dp, ptr, path, stct);
    closedir(ptr);
    free(path);
    return (0);
}