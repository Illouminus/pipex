/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:17:52 by edouard           #+#    #+#             */
/*   Updated: 2024/01/15 13:52:48 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*loc;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		size = 1;
		nmemb = size;
	}
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	loc = malloc(nmemb * size);
	if (!loc)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *)loc)[i] = 0;
		i++;
	}
	return (loc);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	len_s1 = i;
	i = 0;
	while (s2[i])
	{
		str[len_s1 + i] = s2[i];
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*loc;
	size_t	i;

	loc = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!loc)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		loc[i] = s1[i];
		i++;
	}
	loc[i] = 0;
	return (loc);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
