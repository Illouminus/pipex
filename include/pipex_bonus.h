#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../libft/libft.h"

// bool check_args(int argc, char **argv);
void ft_free_tab(char **tab);
char *get_path(char *cmd, char **env);
#endif