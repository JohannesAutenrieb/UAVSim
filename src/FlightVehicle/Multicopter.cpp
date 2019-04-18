/**
 *
 * File: Multicopter.cpp
 * Class name: Multicopter
 * Purpose: This Class Multicopter brings all subsystems instances of the multicopter togehter and it also storing all the technical information of the multicopter.
 *          It also triggering the calcultion of the subsystem.
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#include"Multicopter.hpp"

Multicopter::Multicopter(const std::string &relativ_path_to_xml):
relativ_path_to_xml(relativ_path_to_xml),
total_mass(0),
moment_of_intertia_jxx(0),
moment_of_intertia_jyy(0),
moment_of_intertia_jzz(0),
number_of_rotors(0),
configuration_typ(0),
rack_weight(0),
devices_and_wire_weight(0),
propeller(relativ_path_to_xml),
load_weight(0)
{
   //loading of xml
    pugi::xml_document doc;
    std::stringstream ss;
    pugi::xml_parse_result result = doc.load_file(relativ_path_to_xml.c_str());
    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
    pugi::xml_node multicoper_data = doc.child("Multicopter").child("Multicopter_FlightVehicle_Data").child("Multicopter");

    //reading the variables and write them in to the attributes
    ss<<multicoper_data.child_value("total_mass");
    ss>>total_mass;
    ss.str("");
    ss.clear();
    //std::cout << "Gewicht: " <<total_mass<<endl;
    ss<<multicoper_data.child_value("moment_of_intertia_jxx");
    ss>>moment_of_intertia_jxx;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("moment_of_intertia_jyy");
    ss>>moment_of_intertia_jyy;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("moment_of_intertia_jzz");
    ss>>moment_of_intertia_jzz;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("number_of_rotors");
    ss>>number_of_rotors;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("rack_weight");
    ss>>rack_weight;
    ss.str("");
    ss.clear();
    ss<<multicoper_data.child_value("load_weight");
    ss>>load_weight;
    ss.str("");
    ss.clear();


    //loading the defined rotor systems
    for(int i=0;i<number_of_rotors;i++)
    {
        propeller_system.push_back(relativ_path_to_xml);
    }

    pugi::xml_node propeller_data=multicoper_data.child("Rotors");

    //iterating over all defined propeller
    int j=0;
    for (pugi::xml_node tool = propeller_data.child("Propeller"); tool; tool = tool.next_sibling("Propeller"))
    {
        //tilt angle loading
        double tilt_angle=0.0;
        ss<<tool.child_value("tilt_angle");
        ss>>tilt_angle;
        ss.str("");
        ss.clear();
        propeller_system[j].setTilt_angle(tilt_angle);

        //position angle loading
        double position_angle=0.0;
        ss<<tool.child_value("position_angle");
        ss>>position_angle;
        ss.str("");
        ss.clear();
        propeller_system[j].setPosition_angle(position_angle);
        j++;
    }

}

void Multicopter::calculate_propulsion_systems(double density, double control_input_1, double control_input_2, double control_input_3, double control_input_4)
{
    //not need anymore
}

double Multicopter::getThrust() const
{
    return thrust;
}

void Multicopter::setThrust(double value)
{
    thrust = value;
}

double Multicopter::getTorque() const
{
    return torque;
}

void Multicopter::setTorque(double value)
{
    torque = value;
}

double Multicopter::getTotal_mass() const
{
    return total_mass;
}

void Multicopter::setTotal_mass(double value)
{
    total_mass = value;
}

double Multicopter::getMoment_of_intertia_jxx() const
{
    return moment_of_intertia_jxx;
}

void Multicopter::setMoment_of_intertia_jxx(double value)
{
    moment_of_intertia_jxx = value;
}

double Multicopter::getMoment_of_intertia_jyy() const
{
    return moment_of_intertia_jyy;
}

void Multicopter::setMoment_of_intertia_jyy(double value)
{
    moment_of_intertia_jyy = value;
}

int Multicopter::getNumber_of_rotors() const
{
    return number_of_rotors;
}

void Multicopter::setNumber_of_rotors(int value)
{
    number_of_rotors = value;
}

int Multicopter::getConfiguration_typ() const
{
    return configuration_typ;
}

void Multicopter::setConfiguration_typ(int value)
{
    configuration_typ = value;
}

double Multicopter::getMoment_of_intertia_jzz() const
{
    return moment_of_intertia_jzz;
}

void Multicopter::setMoment_of_intertia_jzz(double value)
{
    moment_of_intertia_jzz = value;
}


