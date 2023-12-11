/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:28:04 by mito              #+#    #+#             */
/*   Updated: 2023/12/11 16:14:58 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

char	*get_next_line(int fd);
char	*read_line(int fd, char *remainder);
char	*find_newline(char **buffer);
char	*free_str(char **str);
size_t	ft_strlen(char *str);
char	*ft_strndup(char *s1, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);

#endif
