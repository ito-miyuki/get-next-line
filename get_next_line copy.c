/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/12/09 14:53:10 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/*
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
	if (s1 || s2) // chaanged AND to OR
	{
		res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!res)
			return (NULL);
		i = 0;
		j = 0;
		if (!res)
			return (NULL);
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
	size_t		i;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	while (s1[i] != '\0' && (i < n || n == 0))
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}


char	*free_str(char **str)
{
	if(*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
*/
/*

char *read_line(int fd, char *remainder)
{
	int chars_read;
    char buffer[BUFFER_SIZE + 1];
	char *temp;

    	while(!(ft_strchr(remainder, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read < 0)
		{
			if(remainder)
			{
				free(remainder);
				remainder = NULL;
			}
			return (NULL);
		}
		if (chars_read <= 0)
			break;
		buffer[chars_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
			return (NULL);
		free(remainder);
		remainder = temp;
	}
	return (remainder);
}


char *find_newline(char **buffer)
{
	char		*newline;
	char		*line;
	int			line_len;
	char		*temp;
	
	newline = ft_strchr(*buffer, '\n');
	if (newline)
		line_len = newline - *buffer + 1;
	else
		line_len = ft_strlen(*buffer);

	line = ft_strndup(*buffer, line_len);
	if (!line)
		return (NULL);
	if (newline && *(newline + 1) != '\0')
	{
		temp = ft_strndup(newline + 1, ft_strlen(newline + 1));
		if (!temp)
			return (NULL);
		if(*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		*buffer = temp;
	}
	else
	{
		if(*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	//char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	//int			chars_read;

	if (!remainder)
	{
		remainder = ft_strndup("", 0);
		if (!remainder)
			return (NULL);
	}
	temp = read_line(fd, remainder);
	if (*remainder == '\0') // if it's the end of file
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	find_newline(&remainder);
	return (temp);
}

int main()
{
 int    fd;
 char   *line;
 int    lines;

 lines = 1;
 fd = open("test_short.txt", O_RDONLY);

 while ((line = get_next_line(fd)))
    printf("%d->%s\n", lines++, line);

close(fd);

return (0);
}
*/

//before split
char *find_newline(char **buffer)
{
	char		*newline;
	char		*line;
	int			line_len;
	char		*temp;
	
	newline = ft_strchr(*buffer, '\n');
	if (newline)
		line_len = newline - *buffer + 1;
	else
		line_len = ft_strlen(*buffer);

	line = ft_strndup(*buffer, line_len);
	if (!line)
		return (NULL);
	if (newline && *(newline + 1) != '\0')
	{
		temp = ft_strndup(newline + 1, ft_strlen(newline + 1));
		if (!temp)
			return (NULL);
		if(*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		*buffer = temp;
	}
	else
	{
		if(*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
	}
	return (line);
}


//↓before splitt
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			chars_read;

	if (!remainder)
	{
		remainder = ft_strndup("", 0);
		if (!remainder)
			return (NULL);
	}
	while(!(ft_strchr(remainder, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read < 0)
		{
			if(remainder)
			{
				free(remainder);
				remainder = NULL;
			}
			return (NULL);
		}
		if (chars_read <= 0)
			break;
		buffer[chars_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
			return (NULL);
		free(remainder);
		remainder = temp;
	}
	if (*remainder == '\0') // if it's the end of file
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (find_newline(&remainder));
}
/*
int main()
{
 int    fd;
 char   *line;
 int    lines;

 lines = 1;
 fd = open("test_short.txt", O_RDONLY);

 while ((line = get_next_line(fd)))
    printf("%d->%s\n", lines++, line);
return (0);
}
*/