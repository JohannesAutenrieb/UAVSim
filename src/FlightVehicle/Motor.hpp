/**
 *
 * File: Motor.cpp
 * Class name: ESC
 * Purpose: This Class Motor Class is includes function which are calculating the behavior of the proppeler motor
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _MOTOR_HXX
#define _MOTOR_HXX
#include <iostream>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include"../../lib/pugixml/pugixml.hpp"
using namespace std;

class Motor
{
    friend class Multicopter;

    public:
       Motor(const std::string &relativ_path_to_xml);
       void    calculate(double proppeler_speed, double torque);
       double getEquivalent_current() const;
       void setEquivalent_current(double value);
       double getEquivalent_voltage() const;
       void setEquivalent_voltage(double value);

    private:
       //Motor input paramter
        double  nominal_noLoad_current;
        double  noload_current;
        double  nominal_noLoad_voltage;
        double  nominal_noLoad_motor_constant;
        double  maximum_current;
        double  resistance;
        double  weight;
        boost::numeric::ublas::matrix<double> distance_of_rotor_to_cg;
        //Motor model variables
        double  back_electromotive;
        double  force_constant;
        double  torque_constant;
        double  equivalent_current;
        double  equivalent_voltage;

};
#endif // _MOTOR_HXX
