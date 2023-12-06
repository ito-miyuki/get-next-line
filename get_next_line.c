/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/12/06 12:31:25 by mito             ###   ########.fr       */
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
	char		*line;
	int			line_len;
	char		*temp;
	
	newline = ft_strchr(*buffer, '\n');
	if (newline)
		line_len = newline - *buffer + 1;
	else
		line_len = ft_strlen(*buffer);

	line = ft_strndup(*buffer, line_len);
	if (newline && *(newline + 1) != '\0')
	{
		temp = ft_strndup(newline + 1, ft_strlen(newline + 1));
		if((*buffer))
		{
			free(*buffer);
			*buffer = NULL;
		}
		*buffer = temp;
	}
	else
	{
		if((*buffer))
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
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			chars_read;

	if (!remainder)
		remainder = ft_strndup("", 0);
	while(!(ft_strchr(remainder, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read < 0)
		{
			if((remainder))
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
