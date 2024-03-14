/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:32:23 by edouard           #+#    #+#             */
/*   Updated: 2024/03/11 19:18:44 by edouard          ###   ########.fr       */
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

void parent(char **argv, int *fd_m, char **env)
{
	int fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error opening file for writing");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd_m[0], STDIN_FILENO);
	close(fd_m[1]);
	close(fd);
	exec(argv[3], env);
}

void child(char **argv, int *fd_m, char **env)
{
	int fd;
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Error opening file for reading");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	dup2(fd_m[1], STDOUT_FILENO);
	close(fd_m[0]);
	close(fd);
	exec(argv[2], env);
}

int main(int argc, char **argv, char **env)
{
	int fd[2];
	pid_t pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child(argv, fd, env);
	waitpid(pid, NULL, 0);
	parent(argv, fd, env);
	return (0);
}
