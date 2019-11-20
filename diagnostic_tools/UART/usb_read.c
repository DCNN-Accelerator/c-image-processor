#include <stdio.h> 
#include <stdio.h>   
#include <string.h>  
#include <unistd.h>  
#include <fcntl.h>   
#include <errno.h>   
#include <termios.h> 
#include <signal.h>
#include <sys/time.h>

#define PORT "/dev/ttyUSB1"
#define BAUDRATE B9600 

int main()
{
    short portfd=-1;
    int n,f,len;
    char buf[256],*s;
    alarm(2); //error handler
    struct termios oldtio,newtio;
    printf("BAUDRATE: %X\nCRTSCTS:  %X\n", BAUDRATE, CRTSCTS);
    printf("CS8:      %X\nCREAD:    %X\nCLOCAL:   %X\n", CS8, CREAD, CLOCAL);
    
#if defined(O_NDELAY) && defined(F_SETFL)
    portfd = open(PORT, O_RDWR|O_NDELAY|O_NOCTTY);
    if (portfd >= 0){
        /* Cancel the O_NDELAY flag. */
        printf("port opened\n");                        //DEBUG
        //sleep(10);
        
        tcgetattr(portfd,&oldtio); 
        printf("got old attributes\n");                 //DEBUG

        // set attributes - these flags may change for your device
        memset(&newtio, 0x00, sizeof(newtio)); 
        printf("past memset\n");                        //DEBUG
        
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CREAD & ~CLOCAL;
        newtio.c_iflag = IGNPAR | ICRNL & ~IXON & ~IXOFF;          
        newtio.c_oflag = 0;  
        newtio.c_lflag = ECHO;
        
        printf("c_cflag: %04X\n", newtio.c_cflag);        //DEBUG
        
        newtio.c_cc[VMIN] = 1;
        newtio.c_cc[VTIME] = 5;

        tcflush(portfd, TCIFLUSH);  
        tcsetattr(portfd,TCSANOW,&newtio); 

        //reset attributes
        //tcsetattr(portfd,TCSANOW,&oldtio); 
        printf("set port attributes\n");                //DEBUG
        
        n = fcntl(portfd, F_GETFL, 0);
        (void) fcntl(portfd, F_SETFL, n & ~O_NDELAY);
    }
#else
    portfd = open(PORT, O_RDWR);
#endif
    if (portfd >= 0) 
    {
        printf("time to read\n");                       //DEBUG
        ssize_t size = read(portfd, buf, 1);
        
        if (len == 0) len = strlen(s);
        printf("past len check\n");                     //DEBUG
        for(f = 0; f < len && f <100; f++)
            buf[f] = *s++ | 0x80;
        printf("past for loop\n");                      //DEBUG
        write(portfd, buf, f);
        
        printf("Do write\n");
        while(portfd>=0){
            printf("%s\n",buf);
        }
    }

    alarm(0);
    signal(SIGALRM, SIG_IGN);
    if (portfd < 0) {
        printf("cannot open %s. Sorry.\n", PORT);
    }
}