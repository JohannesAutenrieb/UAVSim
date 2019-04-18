/**
 *
 * File: FlightDynamic.cpp
 * Class name: FlightDynamic
 * Purpose: This Class is calculating the Multicopter movement and flight behavior
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#define PI 3.14159265
#define FROM_DEGREE_TO_RADIAN PI/180

#include"FlightDynamic.hpp"




FlightDynamic::FlightDynamic(Multicopter &multicopter):
multicopter(multicopter)
{
  //  #define PI 3.14159265
    from_degree_to_radian=3.14159265/180;

}
/**
 * Method description.
 * @param integration_time_step  description: time of integrating, normaly the frequenz time of the thread timer
 * @param control_input          description: control input for controling the multicopter
 * @return void                  description:
 * @since 15.06.2017
 * @author Johannes Autenrieb
 */

void FlightDynamic::calculation(double integration_time_step, unsigned short elevator, unsigned short aileron, unsigned short rudder, unsigned short throttle)
{
    //###STEP 1: Calculating current density
    //1.calculating atmosphere parameters
    std::cout<<"density:"<<atmosphere.getDensity(flightMode.position.altitude)<<endl;   //printout

    //###STEP 2: Calculating&storing all Forces&Moments
    //1.need to calculate thrust and torque for all rotors

    /*!!!! Here the control modul has to be included to set the motor triger input for the*/
    flightMode.controlInput.aileron=aileron;
    flightMode.controlInput.elevator=elevator;
    flightMode.controlInput.throttle=throttle;
    flightMode.controlInput.rudder=rudder;


    //here we need to implement the controler system to give as parameter the proplusion scaling input
    for (vector<int>::size_type i=0; i<multicopter.propeller_system.size(); ++i)
    {
        multicopter.propeller_system[i].calculate(atmosphere.getDensity(flightMode.position.altitude),0);
    }
    //2.calculating of all Forces in body frame cordinate system
    forces_in_body_frame.x=0;
    forces_in_body_frame.y=0;
    forces_in_body_frame.z=0;
    //x-direcetion

    cout <<"forces of thrust loop:"<<multicopter.propeller_system[0].getTilt_angle()<<endl;
    cout <<"forces of thrust loop:"<<multicopter.propeller_system[1].getTilt_angle()<<endl;
    cout <<"forces of thrust loop:"<<multicopter.propeller_system[2].getTilt_angle()<<endl;
    cout <<"angle:"<<multicopter.propeller_system[3].getThrust()<<endl;


    for (vector<int>::size_type i=0; i<multicopter.propeller_system.size(); ++i)
    {
        forces_in_body_frame.x+= multicopter.propeller_system[i].getThrust()*sin(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle())*cos(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getPosition_angle());
        cout <<"forces in x:"<<forces_in_body_frame.x<<endl;
    }
    //y-direction
    for (vector<int>::size_type i=0; i<multicopter.propeller_system.size(); ++i)
    {
        forces_in_body_frame.y+= multicopter.propeller_system[i].getThrust()*sin(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle())*sin(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getPosition_angle());
    }
    //z-direction
    for (vector<int>::size_type i=0; i<multicopter.propeller_system.size(); ++i)
    {
        forces_in_body_frame.z+= (-1)*multicopter.propeller_system[i].getThrust()*cos(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle());
    }
    cout <<"forces in z direction:"<<forces_in_body_frame.z<<endl;

    //additional computing of gravity influence
    forces_in_body_frame.z+=(gravitation_on_earth/multicopter.getTotal_mass());

    //3.calculating of all moments in body frame cordinate systeme
    momentums.x=0;
    momentums.y=0;
    momentums.z=0;
    //x-Momentum
    for (vector<int>::size_type i=0.00; i<multicopter.propeller_system.size(); ++i)
    {
        momentums.x+= (-1)*multicopter.propeller_system[i].getThrust()*sin(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getPosition_angle())*sin(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle());
    }
    //y-Momentum
    for (vector<int>::size_type i=0; i<multicopter.propeller_system.size(); ++i)
    {
        momentums.y+= multicopter.propeller_system[i].getThrust()*cos(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getPosition_angle())*sin(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle());
    }
    //z-Momentum
    for (vector<int>::size_type i=0; i<multicopter.propeller_system.size(); ++i)
    {
        //changing sign in each run, to equalize the torques of all propellers
        if(i==0)
        {
            momentums.z+= (-1)*multicopter.propeller_system[i].getTorque()*cos(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle());
        }
        else if(fmod(i,2)>0)
        {
            momentums.z+= multicopter.propeller_system[i].getTorque()*cos(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle());
        }
        else
        {
            momentums.z+= (-1)*multicopter.propeller_system[i].getTorque()*cos(FROM_DEGREE_TO_RADIAN*multicopter.propeller_system[i].getTilt_angle());
        }

    }

    std::cout<<"Momemntum in x:"<<momentums.x<<endl;
    std::cout<<"Momemntum in y:"<<momentums.y<<endl;
    std::cout<<"Momemntum in z:"<<momentums.z<<endl;

    //###STEP 3: Define Equations of motions
    //1.translation
    //flightMode.translational_acceleration.x_dot_dot=forces_in_body_frame.x*(sin(flightMode.attitude.psi)*sin(flightMode.attitude.phi)+cos(flightMode.attitude.psi)*sin(flightMode.attitude.theta)*cos(flightMode.attitude.phi))/multicopter.getTotal_mass();
    //flightMode.translational_acceleration.y_dot_dot=forces_in_body_frame.y*(sin(flightMode.attitude.psi)*sin(flightMode.attitude.theta)*cos(flightMode.attitude.phi)+cos(flightMode.attitude.psi)*sin(flightMode.attitude.phi))/multicopter.getTotal_mass();
    //flightMode.translational_acceleration.z_dot_dot=forces_in_body_frame.z*(cos(flightMode.attitude.phi)*cos(flightMode.attitude.theta))/multicopter.getTotal_mass() - gravitation_on_earth;

    flightMode.translational_acceleration.x_dot_dot=(cos(flightMode.attitude.psi)*cos(flightMode.attitude.theta))*forces_in_body_frame.x + (cos(flightMode.attitude.psi)*sin(flightMode.attitude.theta)*sin(flightMode.attitude.phi)-cos(flightMode.attitude.phi)*sin(flightMode.attitude.psi))*forces_in_body_frame.y+(sin(flightMode.attitude.theta)*sin(flightMode.attitude.psi)+cos(flightMode.attitude.phi)*cos(flightMode.attitude.psi)*sin(flightMode.attitude.theta))*forces_in_body_frame.z;
    flightMode.translational_acceleration.y_dot_dot=(sin(flightMode.attitude.psi)*cos(flightMode.attitude.theta))*forces_in_body_frame.x+(cos(flightMode.attitude.phi)*cos(flightMode.attitude.psi)-sin(flightMode.attitude.phi)*sin(flightMode.attitude.psi)*sin(flightMode.attitude.theta)*cos(flightMode.attitude.phi))*forces_in_body_frame.y+(sin(flightMode.attitude.psi)*sin(flightMode.attitude.theta)-cos(flightMode.attitude.psi)*sin(flightMode.attitude.phi))*forces_in_body_frame.z;
    flightMode.translational_acceleration.z_dot_dot=((-1)*sin(flightMode.attitude.theta))*forces_in_body_frame.x+(sin(flightMode.attitude.phi)*cos(flightMode.attitude.theta))*forces_in_body_frame.y+(cos(flightMode.attitude.theta)*cos(flightMode.attitude.phi))*forces_in_body_frame.z;

    //###STEP 4:Solve equations of motions

    std::cout<<"acce in z:"<<flightMode.translational_acceleration.z_dot_dot<<endl;

     //2.rotation
    flightMode.rotational_acceleration.p_dot=momentums.x/multicopter.getMoment_of_intertia_jxx()+(((multicopter.getMoment_of_intertia_jyy()-multicopter.getMoment_of_intertia_jzz())/(multicopter.getMoment_of_intertia_jxx())))*flightMode.rotational_velocity.q*flightMode.rotational_velocity.r;
    flightMode.rotational_acceleration.q_dot=momentums.y/multicopter.getMoment_of_intertia_jyy()+(((multicopter.getMoment_of_intertia_jzz()-multicopter.getMoment_of_intertia_jxx())/(multicopter.getMoment_of_intertia_jyy())))*flightMode.rotational_velocity.p*flightMode.rotational_velocity.r;
    flightMode.rotational_acceleration.r_dot=momentums.z/multicopter.getMoment_of_intertia_jzz()+(((multicopter.getMoment_of_intertia_jxx()-multicopter.getMoment_of_intertia_jyy())/(multicopter.getMoment_of_intertia_jzz())))*flightMode.rotational_velocity.p*flightMode.rotational_velocity.q;

    std::cout<<"Angel Acceleration in x:"<<flightMode.rotational_acceleration.p_dot<<endl;
    std::cout<<"Angel Acceleration in y:"<<flightMode.rotational_acceleration.q_dot<<endl;
    std::cout<<"Angel Acceleration in z:"<<flightMode.rotational_acceleration.r_dot<<endl;


    //###solving the equation in first approach with euler method(easy and fast, but maybe rugnge-kutta better)
    //1.translational movement
    //translational velocityhtMode.translational_acceleration.x_dot_dot*integration_time_step;
    flightMode.translational_velocity.y_dot+=flightMode.translational_acceleration.y_dot_dot*integration_time_step;
    flightMode.translational_velocity.z_dot+=flightMode.translational_acceleration.z_dot_dot*integration_time_step;
     std::cout<<"integrationszeit:"<<integration_time_step<<endl;

     std::cout<<"velo in z:"<<flightMode.translational_velocity.z_dot<<endl;

    //delta
    flightMode.position_delta.x= flightMode.translational_acceleration.x_dot_dot*integration_time_step;
    flightMode.position_delta.y= flightMode.translational_acceleration.y_dot_dot*integration_time_step;
    flightMode.position_delta.z= flightMode.translational_acceleration.z_dot_dot*integration_time_step;
     cout <<"position delta in z direction:"<< flightMode.position_delta.z<<endl;

    flightMode.position.x+=flightMode.position_delta.x;
    flightMode.position.y+=flightMode.position_delta.y;
    flightMode.position.z+=flightMode.position_delta.z;
    flightMode.position.altitude+=flightMode.position.z;

    //print out new position
    std::cout<<"FROM_DEGREE_TO_RADIAN"<<FROM_DEGREE_TO_RADIAN<<endl;
    std::cout<<"y:"<<flightMode.position.y<<endl;
    std::cout<<"z:"<<flightMode.position.altitude<<endl;

    //2.rotational movement
    //rotational velocity
    flightMode.rotational_velocity.p=flightMode.rotational_velocity.p + flightMode.rotational_acceleration.p_dot*integration_time_step;
    flightMode.rotational_velocity.q=flightMode.rotational_velocity.q + flightMode.rotational_acceleration.q_dot*integration_time_step;
    flightMode.rotational_velocity.r=flightMode.rotational_velocity.r + flightMode.rotational_acceleration.r_dot*integration_time_step;
    //delta
    flightMode.attitude_delta.phi= flightMode.rotational_velocity.p*integration_time_step;
    flightMode.attitude_delta.theta= flightMode.rotational_velocity.q*integration_time_step;
    flightMode.attitude_delta.psi= flightMode.rotational_velocity.r*integration_time_step;
    //new position
    flightMode.attitude.phi+=flightMode.attitude_delta.phi;
    flightMode.attitude.theta+=flightMode.attitude_delta.theta;
    flightMode.attitude.psi+=flightMode.attitude_delta.psi;
    //print out new alignment
    std::cout<<"x:"<<flightMode.attitude.phi<<endl;
    std::cout<<"y:"<<flightMode.attitude.theta<<endl;
    std::cout<<"z:"<<flightMode.attitude.psi<<endl;
}
