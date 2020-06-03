/*
** Created on Mon Jun 01 2020
**
** Copyright (c) 2020 Virgile Agnel
*/

#ifndef _scsd_h
#define _scsd_h

#include "libc.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

typedef enum byte_s {
    a_Flags = 1,
    d_Flags = 2,
    l_Flags = 4,
    f_Flags = 8,
    D_Flags = 16,
    t_Flags = 32,
} byte;

typedef enum sort_s {
    ALPHA = 1,
    MODIF = 2,
} sort;

typedef enum info_e {
    EMPTY = 0,
    DATE = 1,
} info;

typedef struct masking_s {
    char opt;
    int byte;
    bool arg;
} masking;

typedef struct config_s {
    bool show_hide;
    bool list_dir_only;
    bool follow_symLink;
    bool print_full_path;
    info fileinfo;
    sort order;
} config;

typedef struct file_to_open_s {
    char *name;
    struct file_to_open_s *next;
} file_to_open;

typedef struct file_list_s {
    char *name;
    char *fullpath;
    bool is_dir;
    struct file_list_s *next;
} file_list;

static const masking table[] = {
    {'a', a_Flags, false},
    {'d', d_Flags, false},
    {'l', l_Flags, false},
    {'f', f_Flags, false},
    {'D', D_Flags, true},
    {'t', t_Flags, false},
    {0, 0, false},
};

typedef struct dir_var_s {
    DIR *ptr;
    struct dirent *dp;
} dir_var;

typedef struct global_s {
    config *values;
    file_to_open *list;
} global;

int decode_mask(short const mask, global *stct);
void free_stct(global *stct);
int init_config(global *stct);
int scsd(global *stct, char *path);
void free_file_list(file_list **head);
int recurse_output(file_list *head, global *stct, char *path);
char *my_pathcat(char *dest, char *src);
int sort_list(file_list **head, global *stct);

#endif /* !scsd_h */