/**
 *
 * File: FlightDynamic.hpp
 * Class name: FlightDynamic
 * Purpose: This Class is calculating the Multicopter movement and flight behavior
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/


#ifndef _FLIGHTDYNAMIC_HXX
#define _FLIGHTDYNAMIC_HXX

#include <iostream>
#include <vector>
#include<string>
#include <sstream>
#include<math.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

//include flight vehicle library
#include"../FlightVehicle/Multicopter.hpp"

//include enviroment
#include"../Enviroment/Atmosphere.hpp"
#include"../Enviroment/EnviromentConstants.hpp"

//include flight mode struct
#include"FlightMode.hpp"
#include<stdio.h>

struct Forces_in_body_frame {
    double x;
    double y;
    double z;
    Forces_in_body_frame():x(0),y(0),z(0)
    {
    }
} ;
struct Momentums {
    double x;
    double y;
    double z;
    Momentums():x(0),y(0),z(0)
    {
    }
} ;


class FlightDynamic
{
  public:
  FlightDynamic(Multicopter &multicopter);
  void calculation(double integration_step, unsigned short elevator, unsigned short aileron, unsigned short rudder, unsigned short throttle);
  FlightMode                flightMode;


  private:
  Multicopter               multicopter;
  Atmosphere                atmosphere;
  Forces_in_body_frame      forces_in_body_frame;
  Momentums                 momentums;
  double                     from_degree_to_radian;

};

#endif // _FLIGHTDYNAMIC_HXX
