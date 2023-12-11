
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

# define BUFFER_SIZE 7
# define MAX_FD 1024

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
	if (s1 && s2) // changed AND to OR
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
	size_t	i;

	i = 0;
	copy = malloc(sizeof(char) * (n + 1));
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
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*read_line(int fd, char *remainder)
{
	int		chars_read;
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;

	while (!(ft_strchr(remainder, '\n')))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read < 0)
			return (free_str(&remainder));
		if (chars_read == 0)
			break ;
		buffer[chars_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
		{
			if (remainder)
				return (free_str(&remainder));
		}
		if (remainder)
			free_str(&remainder);
		remainder = temp;
	}
	return (remainder);
}

char	*find_newline(char **buffer)
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
		return (free_str(buffer));
	if (newline && *(newline + 1) != '\0')
	{
		temp = ft_strndup(newline + 1, ft_strlen(newline + 1));
		free_str(buffer);
		if (!temp)
			return (free_str(&line));
		*buffer = temp;
	}
	else
		free_str(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
	{
		remainder = ft_strndup("", 0);
		if (!remainder)
			return (NULL);
	}
	remainder = read_line(fd, remainder);
	if (!remainder || *remainder == '\0')
	{
		return (free_str(&remainder));
	}
	return (find_newline(&remainder));
}

// BONUS
/*
char	*get_next_line(int fd)
{
	static char	*remainder[1024];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder[fd])
	{
		remainder[fd] = ft_strndup("", 0);
		if (!remainder[fd])
			return (NULL);
	}
	remainder[fd] = read_line(fd, remainder[fd]);
	if (!remainder[fd] || *remainder[fd] == '\0')
	{
		return (free_str(&remainder[fd]));
	}
	return (find_newline(&remainder[fd]));
}
*/
//for reading only one file

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

//for reading multiple files
/*
int main()
{
 int    fd;
 int	fd2;
 char   *line;
 int    lines;
 int    lines2;
 int	i;

lines = 1;
lines2 = 1;
fd = open("test.txt", O_RDONLY);
fd2 = open("test_short.txt", O_RDONLY);
while(i < 12)
{
	if ((line = get_next_line(fd)))
	{
		printf("File 1, line %d: %s\n", lines++, line);
		free(line);
	}
	if ((line = get_next_line(fd2)))
	{
		printf("File 2, line %d: %s\n", lines2++, line);
		free(line);
	}
	i++;
}
close(fd);
close(fd2);
}
*/