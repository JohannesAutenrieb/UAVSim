/**
 *
 * File: SerialPortReader.cpp
 * Class name: SerialPortReader
 * Purpose: This Class is encrypting the recieved messages behavior they can be handelt inside of the simualtion
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include "SerialPortReader.hpp"

SerialPortReader::SerialPortReader():
fd(0),
wlen(0),
rdlen(0),
aileron(0),
elevator(0),
throttle(0),
rudder(0)
{

    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", "/dev/ttyUSB0", strerror(errno));

    }
    /*baudrate 9216000, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, 9216000);
    //set_mincount(fd, 0);                /* set to pure timed read */

    /* simple output */
    wlen = write(fd, "Hello!\n", 7);
    if (wlen != 7) {
        printf("Error from write: %d, %d\n", wlen, errno);
    }
    tcdrain(fd);    /* delay for output */
}

SerialPortReader::~SerialPortReader()
{

}

int SerialPortReader::set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void SerialPortReader::set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        //return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0)
        printf("Error tcsetattr: %s\n", strerror(errno));
}


void SerialPortReader::listen()
{

            rdlen = read(fd, buf, sizeof(buf) - 1);
            if (rdlen > 0)
            {
                decode(buf);
            }
            else if (rdlen < 0)
            {
                printf("Error from read: %d: %s\n", rdlen, strerror(errno));
            }
}

void SerialPortReader::decode(unsigned char buf[])
{
    unsigned char *value;
    //poof if package includes the prefix of the reciever message
    value = buf;
    if((*value)==0x82)
    {
        value++;
        if((*value)==0x83)
        {
            value++;

            //-----_>Start decoding and storing of values
            //getting the aileron value
            aileron=*value;
            memcpy(&aileron, value, 2);
            printf("Value for Aileron: %hu \n", aileron);
            value+=2;                                       //incrementing the pointer by 2 bytes

            //getting the elevator value
            elevator=*value;
            memcpy(&elevator, value, 2);
            printf("Value for Elevator: %hu \n", elevator);
            value+=2;

            //getting the elevator value
            throttle=*value;
            memcpy(&throttle, value, 2);
            printf("Value for Throttle: %hu \n", throttle);
            value+=2;

            //getting the elevator value
            rudder=*value;
            memcpy(&rudder, value, 2);
            printf("Value for Rudder: %hu \n", rudder);
            value+=2;

        }

    }
}


unsigned short SerialPortReader::getAileron() const
{
    return aileron;
}

void SerialPortReader::setAileron(unsigned short value)
{
    aileron = value;
}

unsigned short SerialPortReader::getElevator() const
{
    return elevator;
}

void SerialPortReader::setElevator(unsigned short value)
{
    elevator = value;
}

unsigned short SerialPortReader::getThrottle() const
{
    return throttle;
}

void SerialPortReader::setThrottle(unsigned short value)
{
    throttle = value;
}

unsigned short SerialPortReader::getRudder() const
{
    return rudder;
}

void SerialPortReader::setRudder(unsigned short value)
{
    rudder = value;
}
