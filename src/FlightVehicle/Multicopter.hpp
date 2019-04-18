/**
 *
 * File: Multicopter.cpp
 * Class name: Multicopter
 * Purpose: This Class Multicopter brings all subsystems instances of the multicopter togehter and it also storing all the technical information of the multicopter.
 *          It also triggering the calcultion of the subsystem.
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _MULTICOPTER_HXX
#define _MULTICOPTER_HXX
//#include<stdlib.h>
#include <iostream>
#include <vector>
#include<string>
#include <sstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include"../../lib/pugixml/pugixml.hpp"

//integration of flightbvehicle classe
#include"Propeller.hpp"

using namespace std;
class Multicopter
{
    public:
      Multicopter(const std::string &relativ_path_to_xml);
      double getTotal_mass() const;
      void setTotal_mass(double value);
      double getMoment_of_intertia_jxx() const;
      void setMoment_of_intertia_jxx(double value);
      double getMoment_of_intertia_jyy() const;
      void setMoment_of_intertia_jyy(double value);
      int getNumber_of_rotors() const;
      void setNumber_of_rotors(int value);
      int getConfiguration_typ() const;
      void setConfiguration_typ(int value);
      double getMoment_of_intertia_jzz() const;
      void setMoment_of_intertia_jzz(double value);
      void calculate_propulsion_systems(double density, double control_input_1, double control_input_2, double control_input_3, double control_input_4);
      double getThrust() const;
      void setThrust(double value);
      double getTorque() const;
      void setTorque(double value);
      vector<Propeller> propeller_system;
      Propeller   propeller;

    private:
        double  total_mass;
        double  moment_of_intertia_jxx;
        double  moment_of_intertia_jyy;
        double  moment_of_intertia_jzz;
        int     number_of_rotors;
        int     configuration_typ;  //configuration typ can only take 1(x) or 2(y)
        double  rack_weight;
        double  devices_and_wire_weight;
        double  load_weight;
        double thrust;
        double torque;
        std::string relativ_path_to_xml;

};

#endif // _MULTICOPTER_HXX
