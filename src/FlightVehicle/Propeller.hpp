/**
 *
 * File: Propeller.cpp
 * Class name: Propeller
 * Purpose: This Class Propeller is calcualting the thrust and torque of each propeller
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _PROPELLER_HXX
#define _PROPELLER_HXX
#include <iostream>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include"../../lib/pugixml/pugixml.hpp"

//integration of subsystem
#include"Battery.hpp"
#include"Motor.hpp"
#include"ESC.hpp"

using namespace std;

class Propeller
{

    friend class Multicopter;

    public:
      Propeller(const std::string &relativ_path_to_xml);
      void    calculate(double density, double control_input);
      double getThrust() const;
      void setThrust(double value);
      double getTorque() const;
      void setTorque(double value);
      double getPropeller_speed() const;
      void setPropeller_speed(double value);
      double getDistance_of_rotor_to_cg_x() const;
      void setDistance_of_rotor_to_cg_x(double value);
      double getDistance_of_rotor_to_cg_y() const;
      void setDistance_of_rotor_to_cg_y(double value);
      double getDistance_of_rotor_to_cg_z() const;
      void setDistance_of_rotor_to_cg_z(double value);
      double getTorque_coefficent() const;
      void setTorque_coefficent(double value);
      double getThrust_coefficent() const;
      void setThrust_coefficent(double value);
      double getDrag_coefficent() const;
      void setDrag_coefficent(double value);
      double getTilt_angle() const;
      void setTilt_angle(double value);
      double getPosition_angle() const;
      void setPosition_angle(double value);

    private:
        //propeller input paramter
        double  diameter;
        double  pitch;
        double  number_of_blades;
        double  blade_average_chord;
        double  weight;
        //paramter for calculating of coefficent
        double  correction_coefficent_blade;
        double  position_coefficent;
        double  slope_of_lift_curve;
        double  downwash_correction;
        double  aspect_ratio;
        double  zero_lift_angle_of_attack;
        double  zero_lift_drag_coefficent;
        double  oswald_factor;
        bool    coefficens_preestimated;
        double  idle_rotor_speed;
        double  maximum_rotor_speed;
        double  distance_of_rotor_to_cg_x;
        double  distance_of_rotor_to_cg_y;
        double  distance_of_rotor_to_cg_z;
        double  position_angle;
        double  tilt_angle;
        //propeller model parameter
        double  torque_coefficent;
        double  thrust_coefficent;
        double  drag_coefficent;
        //propeller model variables
        double  thrust;
        double  torque;
        double  propeller_speed;
        //subsystem of propulsion
        Battery battery;
        ESC     esc;
        Motor   motor;

};

#endif // _PROPELLER_HXX
