#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

#define DATA_NUM (64)

int main(int argc, char *argv[])
{
    int fd;
    int r_len, w_len;
    char buf[DATA_NUM] = "hello world";
    memset(buf, 0, DATA_NUM);

    fd = open("/dev/hello", O_RDWR);
    printf("fd = %d\n", fd);
    if(fd == -1)
    {
        printf("open error\n");
        return -1;
    }
    else 
    {
        printf("open success\n");
    }

    w_len = write(fd, buf, DATA_NUM);
    r_len = read(fd, buf, DATA_NUM);
    printf("r_len = %d\n", r_len);
    printf("w_len = %d\n", w_len);
    printf("buf = %s\n", buf);
    close(fd);

    return ;
}