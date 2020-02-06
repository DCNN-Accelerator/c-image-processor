#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define PORT "/dev/ttyUSB1"

int main(){
    char byte;
    speed_t baud = B9600;
    int fd = open(PORT, O_RDWR);
    
    struct termios settings;
    tcgetattr(fd, &settings);
    
    cfsetospeed(&settings, baud);
    settings.c_cflag &= ~PARENB;
    settings.c_cflag &= ~CSTOPB;
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8 | CRTSCTS;
    settings.c_lflag = ICANON;
    settings.c_oflag &= ~OPOST;
    
    tcsetattr(fd, TCSANOW, &settings);
    tcflush(fd, TCOFLUSH);
    
    ssize_t size = read(fd, &byte, 1);
    printf("Read byte %c\n", byte);
    
    close(fd);
    return 0;
}
