#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
int main(){
    char byte[4];
    int fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY);
    
    int RTS_flag;
    RTS_flag = TIOCM_RTS;
    ioctl(fd, TIOCMBIS, &RTS_flag);
    ssize_t size = read(fd, &byte, 4);
    ioctl(fd, TIOCMBIC, &RTS_flag);
    printf("Read byte %s\n", byte);
    return 0;
}