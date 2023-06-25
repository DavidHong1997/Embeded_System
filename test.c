#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
//#include <fcntl.h> // for open
#include <unistd.h> // for close
#define BAUDRATE        B9600  //baud rate value
#define MODEMDEVICE     "/dev/tty.usbserial-1420" //Mac usb port
#define _POSIX_SOURCE   1
/*** global value ***/
int fd, c = 0, res;
struct termios oldtio, newtio;
char  buf[256];
/*** Rs232 close sept ***/
void Rs232Init();
void CloseSept();
void Rs232PortOpen();
void ReadDate();

/** main function **/
int main (void)
{
    printf("Rs232 Start...\n");
    /** USB port open **/
    Rs232PortOpen();
    return 0;
}

void CloseSept()
{
    printf("Rs232 Close...\n");
    close(fd);
    tcsetattr(fd, TCSANOW, &oldtio);
}
/* read Data */
void ReadDate()
{
    /** Rs232 read Date **/
    while(1)
    {
        /**讀取數據**/
        res = read(fd, buf, 255);
        if(res == -1)
        {
            //res = -1 表示沒有讀取到數據
            printf(" Rs232 Read Error \n");
        }
        buf[res]=0;
        printf("res = %d  buf = %s \n", res, buf);
        //判斷接收到＠就停止
        if (buf[0] == '@')
        {
            break;
        }
    }
    /*** Rs232 close sept ***/
    CloseSept();
}
/* port open */
void Rs232PortOpen()
{
    /*** Open USB Port ***/
    fd = open(MODEMDEVICE,O_RDWR|O_NOCTTY);
    if(fd < 0)
    {
        perror(MODEMDEVICE);
    }
    printf("USB Port Open...\n");
    /** Rs232 init **/
    Rs232Init();
}
/** init **/
void Rs232Init()
{
    /** Rs232 Init function **/
    tcgetattr(fd, &oldtio);
    memset(&newtio,0, sizeof(newtio));
    newtio.c_cflag = BAUDRATE|CS8|CLOCAL|CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = ICANON;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);
    printf("Writing...\n");
    /** read Rs232 **/
    ReadDate();
}

