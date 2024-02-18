#ifndef PIPEX_H
#define PIPEX_H

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

bool check_args(int argc, char **argv);

#endif