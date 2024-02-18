/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:17:46 by edouard           #+#    #+#             */
/*   Updated: 2024/01/15 14:30:34 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* read_and_store */
char	*read_from_fd(int fd, char *readed)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, readed, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		readed[bytes_read] = '\0';
		return (readed);
	}
	else
		return (NULL);
}

char	*read_and_store(int fd, char **buffer)
{
	char	*readed;
	ssize_t	bytes_read;
	char	*temp;

	readed = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!readed)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, readed, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		readed[bytes_read] = '\0';
		if (!*buffer)
			*buffer = ft_strdup("");
		temp = *buffer;
		*buffer = ft_strjoin(temp, readed);
		free(temp);
		if (ft_strchr(*buffer, '\n'))
			break ;
	}
	free(readed);
	return (*buffer);
}

/* process_line */
char	*process_line(char **buffer)
{
	char	*line;
	char	*temp;

	temp = ft_strchr(*buffer, '\n');
	if (temp)
	{
		line = ft_substr(*buffer, 0, temp - *buffer + 1);
		temp = ft_strdup(temp + 1);
		free(*buffer);
		*buffer = temp;
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/* get_next_line */
char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_and_store(fd, &buffer) || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (process_line(&buffer));
}

// #include <fcntl.h>

// int main(void)
//{
//	int fd = open("test", O_RDONLY);
//	if (fd < 0)
//	{
//		perror("Error opening file");
//		return (1);
//	}
//
//	char *line;
//	line = get_next_line(fd);
//	printf("%s", line);
//	free(line);
//	//	while ((line = get_next_line(fd)) != NULL)
//	//	{
//	//		printf("%s", line);
//	//		free(line);
//	//	}
//
//	close(fd);
//	return (0);
// }
