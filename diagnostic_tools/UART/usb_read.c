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

int main()
{
    short portfd=-1;
    int n,f,len;
    char buf[256],*s;
    alarm(2);
    struct termios oldtio,newtio;
    
#if defined(O_NDELAY) && defined(F_SETFL)
    portfd = open(PORT, O_RDWR|O_NDELAY);
    if (portfd >= 0){
        /* Cancel the O_NDELAY flag. */
        printf("port openend\n");
        
        tcgetattr(portfd,&oldtio);  

        // set attributes - these flags may change for your device
        #define BAUDRATE B9600 
        memset(&newtio, 0x00, sizeof(newtio));  
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;   
        newtio.c_iflag = IGNPAR | ICRNL;          
        newtio.c_oflag = 0;  

        tcflush(portfd, TCIFLUSH);  
        tcsetattr(portfd,TCSANOW,&newtio); 

        //reset attributes
        tcsetattr(portfd,TCSANOW,&oldtio); 
        
        n = fcntl(portfd, F_GETFL, 0);
        (void) fcntl(portfd, F_SETFL, n & ~O_NDELAY);
    }
#else
    portfd = open(PORT, O_RDWR);
#endif
    if (portfd >= 0) 
    {
        if (len == 0) len = strlen(s);
        for(f = 0; f < len && f <100; f++)
            buf[f] = *s++ | 0x80;
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