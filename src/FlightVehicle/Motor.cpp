/**
 *
 * File: Motor.cpp
 * Class name: ESC
 * Purpose: This Class Motor Class is includes function which are calculating the behavior of the proppeler motor
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include"Motor.hpp"

Motor::Motor(const std::string &relativ_path_to_xml):
nominal_noLoad_current(0),
noload_current(0),
nominal_noLoad_voltage(0),
nominal_noLoad_motor_constant(0),
maximum_current(0),
resistance(0),
weight(0),
back_electromotive(0),
force_constant(0),
torque_constant(0),
equivalent_current(0),
equivalent_voltage(0),
distance_of_rotor_to_cg(3,3)
{
    //loading of xml
     pugi::xml_document doc;
     std::stringstream ss;
     pugi::xml_parse_result result = doc.load_file(relativ_path_to_xml.c_str());
     std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
     pugi::xml_node multicoper_data = doc.child("Multicopter").child("Multicopter_FlightVehicle_Data").child("Motor");

     //reading the variables and write them in to the attributes
     //std::cout << "Gewicht: " << multicoper_data.child_value("total_mass")<<endl;
     ss<<multicoper_data.child_value("nominal_noLoad_current");
     ss>>nominal_noLoad_current;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("noload_current");
     ss>>noload_current;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("nominal_noLoad_voltage");
     ss>>nominal_noLoad_voltage;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("nominal_noLoad_motor_constant");
     ss>>nominal_noLoad_motor_constant;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("maximum_current");
     ss>>maximum_current;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("resistance");
     ss>>resistance;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("weight");
     ss>>weight;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("back_electromotive");
     ss>>back_electromotive;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("force_constant");
     ss>>force_constant;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("torque_constant");
     ss>>torque_constant;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("equivalent_voltage");
     ss>>equivalent_voltage;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("equivalent_current");
     ss>>equivalent_current;
     ss.str("");
     ss.clear();
}
void    Motor::calculate(double proppeler_speed, double torque)
{
    //caluclation of motor model
    back_electromotive=(nominal_noLoad_voltage-nominal_noLoad_current*resistance)/(nominal_noLoad_motor_constant*nominal_noLoad_voltage);
    torque_constant=9.55*back_electromotive;
    equivalent_current=((torque)/(torque_constant))+noload_current;
    equivalent_voltage=(back_electromotive*proppeler_speed)+resistance*equivalent_current;
}

double Motor::getEquivalent_current() const
{
    return equivalent_current;
}

void Motor::setEquivalent_current(double value)
{
    equivalent_current = value;
}

double Motor::getEquivalent_voltage() const
{
    return equivalent_voltage;
}

void Motor::setEquivalent_voltage(double value)
{
    equivalent_voltage = value;
}
