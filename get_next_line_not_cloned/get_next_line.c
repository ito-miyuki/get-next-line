/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:30:15 by mito              #+#    #+#             */
/*   Updated: 2023/11/29 17:20:05 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char    buffer[BUFFER_SIZE + 1];
    int             chars_read;
    char            *str; 

 // add whatever is in buffer to str, or put ""
 //strcpy() <=> strjoin(str, s1, "") - this is how to copy some string using function strjoin
    while (*str != '\n')
    {
        chars_read = read(fd, buffer, BUFFER_SIZE);
        
        if (chars_read  <= 0)
            return NULL;
    }
    //buffer[chars_read] = '\0';
    return (buffer);
}

#include <stdio.h>

int main() {
    int fd;

    char *line = get_next_line(fd);

    if (line != NULL) {
        printf("Read line: %s\n", line);
    } else {
        printf("Error reading line or EOF reached.\n");
    }

    return (0);
}