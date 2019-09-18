#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char** argv){
    int fd = open(argv[1], O_RDWR | O_NOCTTY);
    if(fd < 0) printf("\n ERROR in opening serial port");
    
    struct termios SerialPortSettings;
    tcgetattr(fd, &SerialPortSettings);
    
    cfsetispeed(&SerialPortSettings,argv[2]);
    cfsetospeed(&SerialPortSettings,argv[2]);
    
    SerialPortSettings.c_cflag &= ~PARENB;
    SerialPortSettings.c_cflag &= ~CSTOPB;
    SerialPortSettings.c_cflag &= ~CSIZE;
    SerialPortSettings.c_cflag |= CS8;
    SerialPortSettings.c_cflag |= CRTSCTS;
    SerialPortSettings.c_cflag |= CREAD | CWRITE | CLOCAL;
    
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    
    SerialPortSettings.c_oflag &= ~OPOST;
    
    tcflush(fd, TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0)
        printf("\n ERROR in Setting attributes");
    else
        printf("\n Baud = %s StopBits = 1 Parity = none",argv[2]);
    
    tcflush(fd, TCIFLUSH);
    
    /* Send data to UART module */
    char testStr[32] = "this is a test";
    int n_written = 0;
    while(testStr[n_written] != '\0'){
        write(fd, &testStr[n_written], 1);
        n_written++;
    }
    
    tcflush(fd, TCIFLUSH);
    
    /* Receive data from UART module */
    char read_buf[32];
    int  n_read = 0;
    
    n_read = read(fd, &read_buf, 32);
    
    for(int i = 0; i < n_read; i++)
        printf("%c",read_buf[i]);
    
    
    /* Compare input and output strings */
    int same = 1;
    
    for(int i = 0; (i < n_read) && same; i++){
        if(testStr[i] != read_buf[i])
            same = 0;
    }
    
    if(same)
        printf("\n Success!");
    else
        printf("\n Failure!");
    
    return 0;
}