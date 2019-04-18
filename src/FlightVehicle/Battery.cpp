/**
 *
 * File: Battery.cpp
 * Class name: Battery
 * Purpose: This Class includes the modelling and computation of porpulsion battery
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include"Battery.hpp"

Battery::Battery(const std::string &relativ_path_to_xml):
capacity(0),
resistance(0),
voltage(0),
maximum_discharge_rate(0),
weight(0),
battery_minimum_capacity(0),
distance_of_rotor_to_cg(3,3)
{
    //loading of xml
    pugi::xml_document doc;
    std::stringstream ss;
    pugi::xml_parse_result result = doc.load_file(relativ_path_to_xml.c_str());
    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
    pugi::xml_node multicoper_data = doc.child("Multicopter").child("Multicopter_FlightVehicle_Data").child("Battery");
    ss<<multicoper_data.child_value("capacity");
    ss>>capacity;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("resistance");
    ss>>resistance;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("voltage");
    ss>>voltage;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("maximum_discharge_rate");
    ss>>maximum_discharge_rate;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("weight");
    ss>>weight;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("battery_minimum_capacity");
    ss>>battery_minimum_capacity;
    ss.str("");
    ss.clear();
}

void    Battery::calculate(double input_current, int number_of_blades, double control_current=1)
{
    battery_current=number_of_blades*input_current+control_current;
    hover_endurance=0.06*((capacity-control_current)/(battery_current));
}

double Battery::getVoltage() const
{
    return voltage;
}

void Battery::setVoltage(double value)
{
    voltage = value;
}

double Battery::getResistance() const
{
    return resistance;
}

void Battery::setResistance(double value)
{
    resistance = value;
}
