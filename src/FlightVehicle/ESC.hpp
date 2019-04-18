/**
 *
 * File: ESC.hpp
 * Class name: ESC
 * Purpose: This ESC includes the modelling and computation of porpulsion esc system
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/
#ifndef _ESC_HXX
#define _ESC_HXX
#include <iostream>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include"../../lib/pugixml/pugixml.hpp"
using namespace std;

class ESC
{
    friend class Multicopter;

    public:
         ESC(const std::string &relativ_path_to_xml);
         void    calculate(double equivalent_current, double equivalent_voltage, double battery_voltage, double battery_resistance, int number_of_blades, double control_current);
         double getInput_throttle() const;
         double getInput_current() const;
         void setInput_current(double value);
         double getInput_voltage() const;
         void setInput_voltage(double value);

    private:
         //Motor input paramter
          double  maximum_current;
          double  equivalent_dc_voltage;
          double  resistance;
          double  weight;
          boost::numeric::ublas::matrix<double> distance_of_rotor_to_cg;
          //Motor model variables
          double  circuit_principle;
          double  input_throttle;
          double  input_current;
          double  input_voltage;

};

#endif // _ESC_HXX
