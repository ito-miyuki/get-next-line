#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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