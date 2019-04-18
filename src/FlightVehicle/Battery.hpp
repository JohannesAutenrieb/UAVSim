/**
 *
 * File: Battery.hpp
 * Class name: Battery
 * Purpose: This Class includes the modelling and computation of porpulsion battery
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _BATTERY_HXX
#define _BATTERY_HXX
#include <iostream>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include"../../lib/pugixml/pugixml.hpp"
using namespace std;

class Battery
{
    friend class Multicopter;
    public:
         Battery(const std::string &relativ_path_to_xml);
         void    calculate(double input_current, int number_of_blades, double control_current);
         double getVoltage() const;
         void setVoltage(double value);
         double getResistance() const;
         void setResistance(double value);

    private:
         //Motor input paramter
         double  capacity;
         double  resistance;
          double  voltage;
          double  maximum_discharge_rate;
          double  weight;
          double  battery_minimum_capacity;
          boost::numeric::ublas::matrix<double> distance_of_rotor_to_cg;
          //Motor model variables
          double  battery_current;
          double  hover_endurance;

};

#endif // _BATTERY_HXX
