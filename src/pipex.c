/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:32:23 by edouard           #+#    #+#             */
/*   Updated: 2024/02/18 14:54:59 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void parent(char **argv, int *fd, char **env)
{
}

void child(char **argv, int *fd, char **env)
{
}

int main(int argc, char **argv, char **env)
{
	int fd[2];
	pid_t pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(-1);
	}
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		exit(-1);
	}
	if (!pid)
		child(argv, fd, env);
	parent(argv, fd, env);
	return (0);
}
