/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/12/01 16:06:12 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

//Ola's strjoin
/*
char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *res;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strndup(s2, ft_strclen(s2, '\0')));
    if (!s2)
        return (ft_strndup(s1, ft_strclen(s1, '\0')));
    res = (char *)ft_calloc(\
            (ft_strclen(s1, '\0') + ft_strclen(s2, '\0') + 1), sizeof(char));
    if (!res)
    {
        return (NULL);
    }
    ft_strcat(res, s1);
    ft_strcat(res, s2);
    return (res);
}
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = NULL;
	if (s1 || s2) // chaanged AND to OR
	{
        /*if (!s1)
            return ((char *)s2);
        if (!s2)
            return ((char *)s1);
            */
		res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


//read everything, ignoring buffersize and linebreak
/*
char *get_next_line(int fd) 
{
    static char buffer[BUFFER_SIZE + 1];
    int chars_read;
    char *str = buffer;
    int counter = 0;
    char *result;

while (*str != '\n')
{
	result = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        counter = 0;
        while (counter < BUFFER_SIZE && *str != '\n') 
		{
            chars_read = read(fd, str, 1);
            counter++;
            if (chars_read <= 0)
			{
                if (str == buffer) 
				{
                    free(result);
                    return (NULL);
                } 
				else 
				{
                    *str = '\0';
                    return (buffer);
                }
			}
			str++;
        }
		if (*str == '\n')
			{
				*str = '\0';
				return (buffer);
			}
        result = ft_strjoin(result, buffer);
		*str = '\0';
}
	free(result);
	return (buffer);
}
*/

char	*ft_strchr(const char *str, int c)
{
	char	*newstr;

	newstr = (char *)str;
	while (*newstr != (char)c)
	{
		if (*newstr == '\0')
			return (NULL);
		newstr++;
	}
	return (newstr);
}
char *get_next_line(int fd) 
{
    static char buffer[BUFFER_SIZE + 1];
    char *result;
    int chars_read;

    result = "";
    while(!(ft_strchr(result, '\n')))
    {
        chars_read = read(fd, buffer, BUFFER_SIZE);
        result = ft_strjoin(result, buffer);
    }
    return (result);
}

#include <fcntl.h>

int main() 
{
    int fd;

    fd = open("test.txt", O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *line = get_next_line(fd);

    if (line != NULL) {
        printf("Read line: %s\n", line);
    } else {
        printf("Error reading line or EOF reached.\n");
    }

    line = get_next_line(fd);

    if (line != NULL) {
        printf("Read line: %s\n", line);
    } else {
        printf("Error reading line or EOF reached.\n");
    }

    close(fd);

    return 0;
}
