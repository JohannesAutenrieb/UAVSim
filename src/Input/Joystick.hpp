/**
 *
 * File: Joystick.cpp
 * Class name: Joystick
 * Purpose: This Class is reading the wired Joysticks and use the values as inputs for the simulation enviroment
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include <plib/js.h>
#include<stdio.h>


class Joystick
{
    public:
        Joystick(int id);
        ~Joystick();
        void Read();
        float getRoll_input() const;
        void setRoll_input(float value);
        float getPitch_input() const;
        void setPitch_input(float value);
        float getYaw_input() const;
        void setYaw_input(float value);
        float getThrottle_input() const;
        void setThrottle_input(float value);
        int getButton() const;
        void setButton(int value);

    private:
        int joystick_id;
        jsJoystick   *js;
        float       *ax;
        float    roll_input;
        float    pitch_input;
        float    yaw_input;
        float    throttle_input;
        int      button;
    };
