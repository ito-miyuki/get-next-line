/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:52:28 by mito              #+#    #+#             */
/*   Updated: 2023/12/20 11:11:40 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = NULL;
	if (s1 && s2)
	{
		res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!res)
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i] != '\0')
		{
			res[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
			res[i++] = s2[j++];
		res[i] = '\0';
	}
	return (res);
}

char	*ft_strchr(char *str, int c)
{
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char	*ft_strndup(char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	while (s1[i] != '\0' && i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
