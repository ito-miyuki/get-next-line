/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/11/30 17:27:13 by mito             ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = NULL;
	if (s1 && s2)
	{
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

#define BUFFER_SIZE 5
/*
this one's result:
Read line: It i
Read line:  d
Read line: Of a
Read line: It w
*/
char *get_next_line(int fd) 
{
    static char buffer[BUFFER_SIZE + 1];
    int chars_read;
    char *str = buffer;
    char *result;

	//result = malloc(sizeof(char) * (BUFFER_SIZE + 1));	
    if (*str != '\n') 
    {
        chars_read = read(fd, str, BUFFER_SIZE);

        if (chars_read <= 0)
		{
			if (str == buffer) 
			{
				free(buffer);
				return (NULL);
			} 
			else 
			{
				*str = '\0';
				return (buffer);
			}
		}
    }
	*str = str[chars_read];
	*str = '\0';
    //free(result);
    return (buffer);
}


/*
char *get_next_line(int fd) 
{
    static char buffer[BUFFER_SIZE + 1];
    int chars_read;
    char *str = buffer;
    int counter = 0;
    char *result;

while(1)
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

/*
char *get_next_line(int fd) 
{
    static char buffer[BUFFER_SIZE + 1];
    int chars_read;
    char *str = buffer;
    int counter = 0;

        counter = 0;
        while (counter < BUFFER_SIZE && *str != '\n') 
		{
            chars_read = read(fd, str, 1);
            counter++;
            if (chars_read <= 0)
			{
                if (str == buffer) 
				{
                    free(buffer);
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
	*str = '\0';
	return (buffer);
}
*/


#include <fcntl.h>

int main() {
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

/*
	char *line2 = get_next_line(fd);

    if (line2 != NULL) {
        printf("Read line: %s\n", line2);
    } else {
        printf("Error reading line or EOF reached.\n");
    }

	char *line3 = get_next_line(fd);

    if (line3 != NULL) {
        printf("Read line: %s\n", line3);
    } else {
        printf("Error reading line or EOF reached.\n");
    }

	char *line4 = get_next_line(fd);
	if (line4 != NULL) {
        printf("Read line: %s\n", line4);
    } else {
        printf("Error reading line or EOF reached.\n");
    }

*/

    close(fd);

    return 0;
}
