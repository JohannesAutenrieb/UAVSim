/**
 *
 * File: Atmosphere.cpp
 * Class name: Atmosphere
 * Purpose: This Class is computing the Enviromental effects of the Simultion by using the ISA Standard of the ICAO
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/


#include "Atmosphere.hpp"
#include"EnviromentConstants.hpp"
#include<math.h>

using namespace std;
#include <iostream>
#include <cstdio>

//matrix of standard atmosphere values
const ISA_layer ISA_def[] = {
//        0    1        2        3           4         5      6         7         8
//       id   (m)      (ft)     (Pa)        (inHg)    (K)     (C)      (K/m)     (K/ft)
ISA_layer(0,      0,       0,   101325,    29.92126, 288.15,  15.00,  0.0065,   0.0019812,1.2250),
ISA_layer(1,  11000,   36089,  22632.1,    6.683246, 216.65, -56.50,       0,           0,0.3639),
ISA_layer(2,  20000,   65616,  5474.89,    1.616734, 216.65, -56.50, -0.0010,  -0.0003048,0.0880),
ISA_layer(3,  32000,  104986,  868.019,    0.256326, 228.65, -44.50, -0.0028,  -0.0008534,0.0132),
ISA_layer(4,  47000,  154199,  110.906,   0.0327506, 270.65,  -2.50,       0,           0,0.0014),
ISA_layer(5,  51000,  167322,  66.9389,   0.0197670, 270.65,  -2.50,  0.0028,   0.0008534,0.0008),
ISA_layer(6,  71000,  232939,  3.95642,  0.00116833, 214.65, -58.50,  0.0020,   0.0006096,0.0002),
ISA_layer(7,  80000,  262467,  0.88628, 0.000261718, 196.65, -76.50,  0.0,      0.0,1.9E-5),
// The last layer MUST have -1.0 for its 'lapse' field
ISA_layer(8,  1.0e9,  3.28e9,  0.00001, 3.0e-9,        2.73, -270.4,  -1.0)
};


Atmosphere::Atmosphere()
{

}
/**
 * Method description.
 * @param altitude               description: current altitude of the multicopter
 * @since 15.06.2017
 * @author Johannes Autenrieb
 */
void Atmosphere::calculate(double altitude)
{
    //calculating of all atmosphere values
    getTemperature(altitude);
    getPressure(altitude);
    getDensity(altitude);
    getSoundspeed();
    viscosity = Beta * pow(temperature, 1.5) / (SutherlandConstant + temperature);
    kinematicViscosity = viscosity / density;
}

double Atmosphere::getTemperature(double altitude)
{
    int i=0;
    bool layer_found=false;


    while(layer_found!=true)
    {
        if((altitude>=ISA_def[i].height)&&(altitude<ISA_def[i+1].height))
        {
            //proof if layer is isotherm layer or not
            if(ISA_def[i].lapse!=0)
            {
                temperature=ISA_def[i].temp+ISA_def[i].lapse*(altitude-ISA_def[i].height);
                layer_found=true;

            }
            else
            {
                temperature=ISA_def[i].temp;
                layer_found=true;

            }
        }
        i++;
      }

    return temperature;
}

void Atmosphere::setTemperature(double value)
{
    temperature = value;
}

double Atmosphere::getPressure(double altitude)
{
    unsigned int b=0;
    double pressure = 0.0;
    double Lmb, Exp, Tmb, deltaH, factor;
    int i=0;
    bool layer_found=false;

    while(layer_found!=true)
    {
        if((altitude>=ISA_def[i].height)&&(altitude<ISA_def[i+1].height))
        {
            //proof if layer is isotherm layer or not
            if(ISA_def[i].lapse!=0)
            {
                Lmb = ISA_def[i].lapse;
                Exp = gravitation_on_earth/(specific_gas_constant_of_air*Lmb);
                factor = Tmb/(Tmb + Lmb*deltaH);
                pressure = ISA_def[i].pressure*pow(factor, Exp);
                layer_found=true;;
            }
            else
            {
                pressure = ISA_def[i].pressure*exp(-gravitation_on_earth*deltaH/(specific_gas_constant_of_air*Tmb));
                layer_found=true;;
            }
        }
        i++;
    }
}

void Atmosphere::setPressure(double value)
{
    pressure = value;
}

double Atmosphere::getDensity(double altitude)
{

    unsigned int b=0;
    double Lmb, Exp, Tmb, deltaH, factor;
    int i=0;
    bool layer_found=false;

    while(layer_found!=true)
    {
        if((altitude>=ISA_def[i].height)&&(altitude<ISA_def[i+1].height))
        {
            //proof if layer is isotherm layer or not
            if(ISA_def[i].lapse!=0)
            {
                Lmb = ISA_def[i].lapse;
                Exp = gravitation_on_earth/(specific_gas_constant_of_air*Lmb);
                factor = Tmb/(Tmb + Lmb*deltaH);
                density = ISA_def[i].density*pow(factor, Exp);
                layer_found=true;;
            }
            else
            {
                density = ISA_def[i].density*exp(-gravitation_on_earth*deltaH/(specific_gas_constant_of_air*Tmb));
                layer_found=true;;
            }
        }
        i++;
    }


    return density;
}

void Atmosphere::setDensity(double value)
{
    density = value;
}

double Atmosphere::getSoundspeed()
{
    soundspeed = sqrt(heat_capacity_ratio*specific_gas_constant_of_air*temperature);
    return soundspeed;
}

void Atmosphere::setSoundspeed(double value)
{
    soundspeed = value;
}

double Atmosphere::getDynamicViscosity()
{
    dynamicViscosity = (reference_viscosity*1E-6)*pow(temperature,1.5)/(temperature+SutherlandConstant);
    return dynamicViscosity;
}

void Atmosphere::setDynamicViscosity(double value)
{
    viscosity = value;
}

double Atmosphere::getKinematicViscosity()
{
    kinematicViscosity=dynamicViscosity/density;
    return kinematicViscosity;
}

void Atmosphere::setKinematicViscosity(double value)
{
    kinematicViscosity = value;
}
