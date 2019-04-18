/**
 *
 * File: SerialPortReader.hpp
 * Class name: SerialPortReader
 * Purpose: This Class is encrypting the recieved messages behavior they can be handelt inside of the simualtion
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/
#ifndef _SERIALPORTREADER_HXX
#define _SERIALPORTREADER_HXX
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

class SerialPortReader
{
    public:
        SerialPortReader();
       ~SerialPortReader();
        int set_interface_attribs(int fd, int speed);
        void set_mincount(int fd, int mcount);
        void listen();
        void decode(unsigned char buf[]);

        unsigned short getAileron() const;
        void setAileron(unsigned short value);

        unsigned short getElevator() const;
        void setElevator(unsigned short value);

        unsigned short getThrottle() const;
        void setThrottle(unsigned short value);

        unsigned short getRudder() const;
        void setRudder(unsigned short value);

private:
        int fd;
        int wlen;
        unsigned char buf[40];
        int rdlen;
        unsigned short aileron;
        unsigned short elevator;
        unsigned short throttle;
        unsigned short rudder;

};

#endif // _SERIALPORTREADER_HXX
