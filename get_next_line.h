/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:10:21 by mito              #+#    #+#             */
/*   Updated: 2023/12/09 16:52:39 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
# endif

typedef struct s_list
{
    char    *str_buf;
    struct s_list   *next;
}   t_list;

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
/*
t_list  *find_last_node(t_list *list);
void    copy_str(t_list *list, char *str);
int     len_to_newline(t_list *list);
void    dealloc(t_list **list, t_list *clean_node, char *buf);
void    polish_list(t_list **list);
char    *get_line(t_list *list);
void    append(t_list **list, char *buf);
void    create_list(t_list  **list, int fd);
int     found_newline(t_list *list);
*/

size_t	ft_strlen(char *str);
char	*ft_strndup(char *s1, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
char    *find_newline(char **buffer);
char	*free_str(char **str);


#endif
