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
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
/*
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
	if (s1 || s2) // chaanged AND to OR
	{
        if (!s1)
            return ((char *)s2);
        if (!s2)
            return ((char *)s1);
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
*/
////////////////////////////////////
// linked list solution

void    polish_list(t_list **list)
{
    t_list  *last_node;
    t_list  *clean_node;
    int i;
    int k;
    char    *buf;

    buf = malloc(BUFFER_SIZE + 1);
    clean_node = malloc(sizeof(t_list));
    if (NULL == buf || NULL == clean_node)
        return ;
    last_node = find_last_node(*list);

    i = 0;
    k = 0;
    while (last_node->str_buf[i] != '\0' && last_node->str_buf[i] != '\n')
        ++i;
    while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i])
        buf[k++] = last_node->str_buf[i];
    buf[k] = '\0';
    clean_node->str_buf = buf;
    clean_node->next = NULL;
    dealloc(list, clean_node, buf);
}

char    *get_line(t_list *list)
{
    int     str_len;
    char    *next_str;

    if (NULL == list)
        return (NULL);
    
    str_len = len_to_newline(list);
    next_str = malloc(str_len + 1);
    if (NULL == next_str)
        return (NULL);
    
    copy_str(list, next_str);
    return (next_str);
}

void    append(t_list **list, char *buf)
{
    t_list  *new_node;
    t_list  *last_node;

    last_node = find_last_node(*list);
    new_node = malloc(sizeof(t_list));
    if (NULL == new_node)
        return ;
    if (NULL == last_node)
        *list = new_node;
    else
        last_node->next = new_node;
    
    new_node->str_buf = buf;
    new_node->next = NULL;
}

void    create_list(t_list  **list, int fd)
{
    int     char_read;
    char    *buf;

    while (!found_newline(*list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return ;
        
        char_read = read(fd, buf, BUFFER_SIZE);

        if (!char_read)
        {
            free(buf);
            return ;
        }
        buf[char_read] = '\0';
        append(list, buf);
    }
}

char    *get_next_line(int fd)
{
    static t_list   *list;
    char            *next_line;

    list = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return (NULL);
    
    create_list(&list, fd);

    if (list == NULL)
        return (NULL);
    
    next_line = get_line(list);

    polish_list(&list);
    return (next_line);   
}

int main()
{
 int    fd;
 char   *line;
 int    lines;

 lines = 1;
 fd = open("test.txt", O_RDONLY);

 while ((line = get_next_line(fd)))
    printf("%d->%s\n", lines++, line);
return (0);
}