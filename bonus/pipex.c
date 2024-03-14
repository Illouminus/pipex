/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:32:23 by edouard           #+#    #+#             */
/*   Updated: 2024/03/12 14:54:10 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void exec(char *cmd, char **env)
{
	char **s_cmd;
	char *path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		perror("Error: execve failed");
		free(path);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
	free(path);
}

void here_doc_next(char **av, int *p_fd)
{
	char *next;

	close(p_fd[0]);
	while (1)
	{
		next = get_next_line(0);
		if (ft_strncmp(next, av[2], ft_strlen(av[2])) == 0)
		{
			free(next);
			exit(0);
		}
		ft_putstr_fd(next, p_fd[1]);
		free(next);
	}
}

void here_doc(char **av)
{
	int fd_m[2];
	pid_t pid;

	if (pipe(fd_m) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_next(av, fd_m);
	else
	{
		close(fd_m[1]);
		dup2(fd_m[0], 0);
		wait(NULL);
	}
}

void do_pipe(char *argv, char **env)
{
	int fd_m[2];
	pid_t pid;

	if (pipe(fd_m) == -1)
	{
		perror("Error: pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd_m[0]);
		dup2(fd_m[1], STDOUT_FILENO);
		exec(argv, env);
	}
	else
	{
		close(fd_m[1]);
		dup2(fd_m[0], STDIN_FILENO);
	}
}

int main(int argc, char **argv, char **env)
{
	int i;
	int fd_out;
	int fd_in;

	if (argc < 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		// do_here_doc(argc, argv, env);
		return (0);
	}
	else
	{
		i = 2;
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd_in, STDIN_FILENO);
	}
	while (i < argc - 2)
	{
		do_pipe(argv[i], env);
		i++;
	}
	do_pipe(argv, env);
	dup2(fd_out, STDOUT_FILENO);
	exec(argv[argc - 2], env);
	return (0);
}
