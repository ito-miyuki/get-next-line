#include "get_next_line.h"

/* for reading only one file
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
*/
//for reading multiple files
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