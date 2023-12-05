/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/12/05 16:51:56 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


char *find_newline(char **buffer)
{
	char		*newline;
	char		*temp;
	
	newline = ft_strchr(*buffer, '\n');
	if (newline)
		*newline = '\0';
	temp = ft_strndup(*buffer, ft_strlen(*buffer));
	if (newline && *(newline + 1) != '\0')
		*buffer = ft_strndup(newline + 1, ft_strlen(newline + 1));
	else
	{
		if((*buffer))
		{
			free(*buffer);
			*buffer = NULL;
		}
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			chars_read;

	if (!remainder)
		remainder = ft_strndup("", 0);
	while(!(ft_strchr(remainder, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
			break;
		buffer[chars_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
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

/* before splitting
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			chars_read;
	char		*newline;

	if (!remainder)
		remainder = ft_strndup("", 0);
	while(!(ft_strchr(remainder, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
			break;
		buffer[chars_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = temp;
	}
	if (*remainder == '\0') // if it's the end of file
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	newline = ft_strchr(remainder, '\n');
	if (newline)
		*newline = '\0';
	temp = ft_strndup(remainder, ft_strlen(remainder));
	if (newline && *(newline + 1) != '\0')
		remainder = ft_strndup(newline + 1, ft_strlen(newline + 1));
	else
	{
		free(remainder);
		remainder = NULL;
	}
	return (temp);
}
*/
/* this is working, do not delete!!!
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			chars_read;
	char		*newline;

	if (!remainder)
		remainder = ft_strndup("", 0);
	while (1)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
			break;
		buffer[chars_read] = '\0';
		//printf("BUFFER: %s\n", buffer);
		temp = ft_strjoin(remainder, buffer);
		//printf("REMAINDER: %s\n", remainder);
		//printf("TEMP: %s\n", temp);
		free(remainder);
		remainder = temp;
		//printf("REMAINDER: %s\n", remainder);
		if (ft_strchr(remainder, '\n') != NULL) // if there is \n in the string
		{
			newline = ft_strchr(remainder, '\n');
			//printf("NEWLINE: %s\n", newline);
			break;
		}
	}
	if (*remainder == '\0') // if it's the end of file
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	newline = ft_strchr(remainder, '\n');
	if (newline)
		*newline = '\0';
	temp = ft_strndup(remainder, ft_strlen(remainder));
	if (newline && *(newline + 1) != '\0')
		remainder = ft_strndup(newline + 1, ft_strlen(newline + 1));
	else
	{
		free(remainder);
		remainder = NULL;
	}
	return (temp);
}
*/

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