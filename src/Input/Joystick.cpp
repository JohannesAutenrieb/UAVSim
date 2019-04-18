/**
 *
 * File: Joystick.cpp
 * Class name: Joystick
 * Purpose: This Class is reading the wired Joysticks and use the values as inputs for the simulation enviroment
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include"Joystick.hpp"


Joystick::Joystick(int id=0):
joystick_id(id),
button(0)
{
    //creating and initaliazation of joystick reader
    jsInit () ;
    js = new jsJoystick ( joystick_id );
    //debug output
    if ( js->notWorking () )
      printf ( "Joystick 0 not detected\n" ) ;
    else
      printf ( "Joystick 0 is \"%s\"\n", js->getName() ) ;

    ax = new float [ js->getNumAxes () ] ;
}
Joystick::~Joystick()
{

}
/**
 * Method description: This Function is reading the Joystick Input
 * @param  -
 * @return void
 * @since 15.06.2017
 * @author Johannes Autenrieb
 */

void Joystick::Read()
{
    //reading joystick axes and write it to input values
    js->read ( &button, ax );
    roll_input=ax[0];
    pitch_input=ax[1];
    yaw_input=ax[2];
    throttle_input=ax[3];
}

float Joystick::getRoll_input() const
{
    return roll_input;
}

void Joystick::setRoll_input(float value)
{
    roll_input = value;
}

float Joystick::getPitch_input() const
{
    return pitch_input;
}

void Joystick::setPitch_input(float value)
{
    pitch_input = value;
}

float Joystick::getYaw_input() const
{
    return yaw_input;
}

void Joystick::setYaw_input(float value)
{
    yaw_input = value;
}

float Joystick::getThrottle_input() const
{
    return throttle_input;
}

void Joystick::setThrottle_input(float value)
{
    throttle_input = value;
}

int Joystick::getButton() const
{
    return button;
}

void Joystick::setButton(int value)
{
    button = value;
}
