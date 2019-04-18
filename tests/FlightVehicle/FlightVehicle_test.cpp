//
// Created by pavel on 12/3/15.
//
#include "gtest/gtest.h"
#include"Multicopter.hpp"
#include "Atmosphere.hpp"

//don't know why,but somehow it only works if both objects are defined as global variables (johannes)
 std::string relativ_path_to_xml("../../FlightVehicleData/multicopter.xml");
 Multicopter multicopter(relativ_path_to_xml);
 Atmosphere atmosphere;


    class FlightVehicleTest : public testing::Test {
    protected:

    };
    //Testing Temperature calculation
   TEST_F(FlightVehicleTest, Proof_of_correct_XML_reading) {
        ASSERT_EQ(1.576,multicopter.getTotal_mass());
    }

   TEST_F(FlightVehicleTest, Correct_moment_of_intertia){
       ASSERT_EQ(15.293E-3,multicopter.getMoment_of_intertia_jxx());
    }

   TEST_F(FlightVehicleTest, Calculate_Thrust_Ground_Idle_Mode) {
        double density=atmosphere.getDensity(0);
        multicopter.calculate_propulsion_systems(density,0.0, 0.0, 0.0, 0.0);
        double calculateted_value=multicopter.getThrust();
        double true_value=109.333;
        ASSERT_EQ(true_value,calculateted_value);
    }
   TEST_F(FlightVehicleTest, Calculate_Thrust_Ground_MaxThrust_Mode) {
       double density=atmosphere.getDensity(0);
       multicopter.calculate_propulsion_systems(density,1, 0.0, 0.0, 0.0);
       ASSERT_EQ(3936,multicopter.getThrust());
   }


