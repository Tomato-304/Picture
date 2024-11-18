#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#define DATA_NUM (32)

int main(int argc, char *argv[])
{
    int fd;
    int r_len, w_len;
    char buf[DATA_NUM] = "hello world";

    fd = open("/dev/hello", O_RDWR);
    printf("fd = %d\n", fd);
    if(fd == -1)
    {
        perror("open file error\n");
        return -1;
    }
    else 
    {
        printf("open file success\n");
    }

    w_len = write(fd, buf, DATA_NUM);
    if(w_len == -1)
    {
        perror("write error\n");
        return -1;
    }

    sleep(20);

    printf("w_len = %d\n", w_len);
    close(fd);

    return 0;
}