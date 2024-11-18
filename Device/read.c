#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>

#define DATA_NUM (32)

int main(int argc, char *argv[])
{
    int fd;
    int r_len;
    char rbuf[DATA_NUM] = "hello world";
    memset(rbuf, 0, DATA_NUM);

    fd = open("/dev/hello", O_RDWR);
    printf("fd = %d\n", fd);
    if(fd == -1)
    {
        printf("open file error\n");
        return -1;
    }
    else 
    {
        printf("open file success\n");
    }

    r_len = read(fd, rbuf, DATA_NUM);
    if(r_len == -1)
    {
        perror("read error\n");
        return -1;
    }
    printf("r_len = %d\n", r_len);
    printf("%s\n", rbuf);
    close(fd);

    return 0;
}