/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/12/04 18:34:36 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_newline(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
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

char	*ft_strndup(char *s1, size_t n)
{
	char	*copy;
	int		i;

	copy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	i = 0;
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

char	*get_next_line(int fd) 
{
	static char *buffer[BUFFER_SIZE + 1];
	char 		*temp;
	int 		chars_read;
	int 		temp_len;
	int			find_newline;
	char		*result;

	temp = ft_strndup("", 0);

	while(!(ft_strchr(temp, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		temp = ft_strjoin(temp, buffer);
	}
	temp_len = ft_strlen(temp);
	find_newline = ft_strlen(ft_strchr(temp, '\n'));
	result = ft_strndup(temp, temp_len - find_newline);

	return (result);
}


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

/*
int main()
{
 int    fd;
 char   buf[256];
 int    chars_read;

 fd = open("test.txt", O_RDONLY);

 while ((chars_read = read(fd, buf, 5)))
 {
    buf[chars_read] = '\0';
    printf("buf-> %s\n", buf);
 }
}

*/
