#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
int main(){
    printf("hello world!\n");
    char byte[4];
    int fd = open("/dev/ttyUSB1", O_RDWR);
    printf("opened port\n");
    
    fcntl(fd, F_SETFL, 0);
    
    int RTS_flag;
    RTS_flag = TIOCM_RTS;
    ioctl(fd, TIOCMBIS, &RTS_flag);
    ssize_t size = read(fd, &byte, 4);
    ioctl(fd, TIOCMBIC, &RTS_flag);
    printf("Read string %s of size %ld\n", byte, size);
    return 0;
}