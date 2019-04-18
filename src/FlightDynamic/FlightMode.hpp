/**
 * File: FlightMode.cpp
 * Class name: -
 * Purpose: This File includes seven structs which are responsibel for the storing of the computed flight behavior
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/


#ifndef _FLIGHTMODE_HXX
#define _FLIGHTMODE_HXX

struct Translational_acceleration {
  double x_dot_dot;
  double y_dot_dot;
  double z_dot_dot;
  Translational_acceleration():x_dot_dot(0),y_dot_dot(0),z_dot_dot(0)
  {
  }
} ;
struct Rotational_acceleration {
    double p_dot;
    double q_dot;
    double r_dot;
    Rotational_acceleration():p_dot(0),q_dot(0),r_dot(0)
    {
    }
} ;
struct Translational_velocity {
    double x_dot;
    double y_dot;
    double z_dot;
    Translational_velocity():x_dot(0),y_dot(0),z_dot(0)
    {
    }
} ;
struct Rotational_velocity {
    double p;
    double q;
    double r;
    Rotational_velocity():p(0),q(0),r(0)
    {
    }
} ;
struct Position_delta {
    double x;
    double y;
    double z;
    Position_delta():x(0),y(0),z(0)
    {
    }
} ;
struct Attitude_delta {
    double phi;
    double theta;
    double psi;
    Attitude_delta():phi(0),theta(0),psi(0)
    {
    }
} ;
struct Position {
    double x;
    double y;
    double z;
    double  altitude;
    Position():x(0),y(0),z(0),altitude(0)
    {
    }
} ;
struct Attitude {
    double phi;
    double theta;
    double psi;
    Attitude():phi(0),theta(0),psi(0)
    {
    }
} ;
struct ControlInput {
    unsigned short aileron;
    unsigned short rudder;
    unsigned short elevator;
    unsigned short throttle;
    ControlInput():aileron(0),rudder(0),elevator(0),throttle(0)
    {
    }
} ;

struct FlightMode {
    Translational_acceleration  translational_acceleration;
    Rotational_acceleration     rotational_acceleration;
    Translational_velocity      translational_velocity;
    Rotational_velocity         rotational_velocity;
    Position_delta              position_delta;
    Attitude_delta              attitude_delta;
    Position                    position;
    Attitude                    attitude;
    ControlInput                 controlInput;

} ;

#endif // _FLIGHTMODE_HXX

