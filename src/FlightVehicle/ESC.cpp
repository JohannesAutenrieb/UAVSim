/**
 *
 * File: ESC.cpp
 * Class name: ESC
 * Purpose: This ESC includes the modelling and computation of porpulsion esc system
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include"ESC.hpp"

ESC::ESC(const std::string &relativ_path_to_xml):
    maximum_current(0),
    equivalent_dc_voltage(0),
    resistance(0),
    weight(0),
    circuit_principle(0),
    input_throttle(0),
    input_current(0),
    input_voltage(0),distance_of_rotor_to_cg(3,3)
{
    //loading of xml
     pugi::xml_document doc;
     std::stringstream ss;
     pugi::xml_parse_result result = doc.load_file(relativ_path_to_xml.c_str());
     std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
     pugi::xml_node multicoper_data = doc.child("Multicopter").child("Multicopter_FlightVehicle_Data").child("ESC");

     //reading the variables and write them in to the attributes
     ss<<multicoper_data.child_value("maximum_current");
     ss>>maximum_current;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("equivalent_dc_voltage");
     ss>>equivalent_dc_voltage;
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
     ss<<multicoper_data.child_value("circuit_principle");
     ss>>circuit_principle;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("input_throttle");
     ss>>input_throttle;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("input_current");
     ss>>input_current;
     ss.str("");
     ss.clear();
}

void    ESC::calculate(double equivalent_current, double equivalent_voltage, double battery_voltage, double battery_resistance, int number_of_blades, double control_current=1)
{
    equivalent_dc_voltage= equivalent_voltage+equivalent_current*resistance;
    input_throttle= equivalent_dc_voltage/input_voltage;
    input_current=input_throttle*equivalent_current;
    //control current is a parameter which got defaulft value of 1, because its usally just 1 Ampere
    input_voltage=battery_voltage-((number_of_blades*input_current+control_current)*battery_resistance);
}

double ESC::getInput_throttle() const
{
    return input_throttle;
}

double ESC::getInput_current() const
{
    return input_current;
}

void ESC::setInput_current(double value)
{
    input_current = value;
}

double ESC::getInput_voltage() const
{
    return input_voltage;
}

void ESC::setInput_voltage(double value)
{
    input_voltage = value;
}
