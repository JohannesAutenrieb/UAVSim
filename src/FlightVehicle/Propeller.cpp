/**
 *
 * File: Propeller.cpp
 * Class name: Propeller
 * Purpose: This Class Propeller is calcualting the thrust and torque of each propeller
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/


#include"Propeller.hpp"

#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
    #include <math.h>
#endif // _USE_MATH_DEFINES

Propeller::Propeller(const std::string &relativ_path_to_xml):
diameter(0),
pitch(0),
number_of_blades(0),
blade_average_chord(0),
weight(0),
correction_coefficent_blade(0),
position_coefficent(0),
slope_of_lift_curve(0),
downwash_correction(0),
aspect_ratio(0),
zero_lift_angle_of_attack(0),
zero_lift_drag_coefficent(0),
oswald_factor(0),
thrust_coefficent(0.0),
battery(relativ_path_to_xml),
esc(relativ_path_to_xml),
motor(relativ_path_to_xml),
torque_coefficent(0.0)
{
    //loading of xml
     pugi::xml_document doc;
     std::stringstream ss;
     pugi::xml_parse_result result = doc.load_file(relativ_path_to_xml.c_str());
     std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
     pugi::xml_node multicoper_data = doc.child("Multicopter").child("Multicopter_FlightVehicle_Data").child("Propeller");

     //reading the variables and write them in to the attributes
     ss<<multicoper_data.child_value("thrust_coefficent");
     ss>>thrust_coefficent;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("torque_coefficent");
     ss>>torque_coefficent;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child("drag_coefficent");
     ss>>drag_coefficent;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("idle_rotor_speed");
     ss>>idle_rotor_speed;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("maximum_rotor_speed");
     ss>>maximum_rotor_speed;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("diameter");
     ss>>diameter;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("pitch");
     ss>>pitch;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("number_of_blades");
     ss>>number_of_blades;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("blade_average_chord");
     ss>>blade_average_chord;
     ss.str("");
     ss<<multicoper_data.child_value("weight");
     ss>>weight;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("correction_coefficent_blade");
     ss>>correction_coefficent_blade;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("position_coefficent");
     ss>>position_coefficent;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("slope_of_lift_curve");
     ss>>slope_of_lift_curve;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("aspect_ratio");
     ss>>aspect_ratio;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("zero_lift_angle_of_attack");
     ss>>zero_lift_angle_of_attack;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("zero_lift_drag_coefficent");
     ss>>zero_lift_drag_coefficent;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("oswald_factor");
     ss>>oswald_factor;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("distance_of_rotor_to_cg_x");
     ss>>distance_of_rotor_to_cg_x;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("distance_of_rotor_to_cg_y");
     ss>>distance_of_rotor_to_cg_y;
     ss.str("");
     ss.clear();
     ss<<multicoper_data.child_value("distance_of_rotor_to_cg_z");
     ss>>distance_of_rotor_to_cg_z;
     ss.str("");
     ss.clear();

}
void    Propeller::calculate(double density, double control_input)
{

    //calculation
    propeller_speed=(idle_rotor_speed+((maximum_rotor_speed-idle_rotor_speed)/(1.0-0.0))*(control_input))/60;
    thrust=thrust_coefficent*pow(propeller_speed,2);
    torque=torque_coefficent*pow(propeller_speed,2);

    //printout for debuging
    cout <<"propeller_speed:"<<propeller_speed<<endl;
    cout <<"thrust:"<<thrust<<endl;
    cout <<"torque:"<<torque<<endl;

    //subsystems
    motor.calculate(propeller_speed,torque);
    esc.calculate(motor.getEquivalent_current(),motor.getEquivalent_voltage(),battery.getVoltage(), battery.getResistance(), number_of_blades,1.0);     //1.0 is the default control curent! In most of cases 1.0, but could be that diffent (Need to be defined in XML)
    battery.calculate(esc.getInput_current(),number_of_blades,1.0);

}

double Propeller::getThrust() const
{
    return thrust;
}

void Propeller::setThrust(double value)
{
    thrust = value;
}

double Propeller::getTorque() const
{
    return torque;
}

void Propeller::setTorque(double value)
{
    torque = value;
}

double Propeller::getPropeller_speed() const
{
    return propeller_speed;
}

void Propeller::setPropeller_speed(double value)
{
    propeller_speed = value;
}

double Propeller::getDistance_of_rotor_to_cg_x() const
{
    return distance_of_rotor_to_cg_x;
}

void Propeller::setDistance_of_rotor_to_cg_x(double value)
{
    distance_of_rotor_to_cg_x = value;
}

double Propeller::getDistance_of_rotor_to_cg_y() const
{
    return distance_of_rotor_to_cg_y;
}

void Propeller::setDistance_of_rotor_to_cg_y(double value)
{
    distance_of_rotor_to_cg_y = value;
}

double Propeller::getDistance_of_rotor_to_cg_z() const
{
    return distance_of_rotor_to_cg_z;
}

void Propeller::setDistance_of_rotor_to_cg_z(double value)
{
    distance_of_rotor_to_cg_z = value;
}

double Propeller::getTorque_coefficent() const
{
    return torque_coefficent;
}

void Propeller::setTorque_coefficent(double value)
{
    torque_coefficent = value;
}

double Propeller::getThrust_coefficent() const
{
    return thrust_coefficent;
}

void Propeller::setThrust_coefficent(double value)
{
    thrust_coefficent = value;
}

double Propeller::getDrag_coefficent() const
{
    return drag_coefficent;
}

void Propeller::setDrag_coefficent(double value)
{
    drag_coefficent = value;
}

double Propeller::getTilt_angle() const
{
    return tilt_angle;
}

void Propeller::setTilt_angle(double value)
{
    tilt_angle = value;
}

double Propeller::getPosition_angle() const
{
    return position_angle;
}

void Propeller::setPosition_angle(double value)
{
    position_angle = value;
}
