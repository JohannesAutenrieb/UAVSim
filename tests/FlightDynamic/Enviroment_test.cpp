//
// Created by pavel on 12/3/15.
//
#include <sstream>
#include "gtest/gtest.h"
#include "Atmosphere.hpp"

namespace {
    class EnviromentTest : public testing::Test {
    protected:
        double altitude;
        double real_pressure;
        Atmosphere atmosphere;

    };
    //Testing Temperature calculation
   TEST_F(EnviromentTest, Calculate_Temperature_0_m) {
        ASSERT_EQ(288.15,atmosphere.getTemperature(0));
    }
   TEST_F(EnviromentTest, Calculate_Temperature_11000_m) {
        ASSERT_EQ(216.65,atmosphere.getTemperature(11000));
    }
   TEST_F(EnviromentTest, Calculate_Temperature_20000_m) {
        ASSERT_EQ(216.65,atmosphere.getTemperature(20000));
    }

   TEST_F(EnviromentTest, Calculate_Temperature_32000_m) {
        ASSERT_EQ(228.65,atmosphere.getTemperature(32000));
    }
   TEST_F(EnviromentTest, Calculate_Temperature_47000_m) {
        ASSERT_EQ(270.65,atmosphere.getTemperature(47000));
    }

   TEST_F(EnviromentTest, Calculate_Temperature_51000_m) {
        ASSERT_EQ(270.65,atmosphere.getTemperature(51000));
    }

   TEST_F(EnviromentTest, Calculate_Temperature_71000_m) {
        ASSERT_EQ(214.65,atmosphere.getTemperature(71000));
    }

   TEST_F(EnviromentTest, Calculate_Temperature_80000_m) {
        ASSERT_EQ(196.65,atmosphere.getTemperature(80000));
    }

   //Testing Pressure calculation
    TEST_F(EnviromentTest, Calculate_Pressure_0_m) {
       ASSERT_EQ(101325,atmosphere.getPressure(0));
   }
    TEST_F(EnviromentTest, Calculate_Pressure_11000_m) {
       ASSERT_EQ(22632.1,atmosphere.getPressure(11000));
    }
    TEST_F(EnviromentTest, Calculate_Pressure_20000_m) {
       ASSERT_EQ(5474.89,atmosphere.getPressure(20000));
    }

    TEST_F(EnviromentTest, Calculate_Pressure_32000_m) {
       ASSERT_EQ(868.019,atmosphere.getPressure(32000));
    }
    TEST_F(EnviromentTest, Calculate_Pressure_47000_m) {
       ASSERT_EQ(110.906,atmosphere.getPressure(47000));
    }

    TEST_F(EnviromentTest, Calculate_Pressure_51000_m) {
       ASSERT_EQ(66.9389,atmosphere.getPressure(51000));
    }

    TEST_F(EnviromentTest, Calculate_Pressure_71000_m) {
       ASSERT_EQ(3.95642,atmosphere.getPressure(71000));
    }

    TEST_F(EnviromentTest, Calculate_Pressure_80000_m) {
      ASSERT_EQ(0.88628,atmosphere.getPressure(80000));
    }

 //Testing Density calculation
    TEST_F(EnviromentTest, Calculate_Density_0_m) {
          ASSERT_EQ(1.2250,atmosphere.getDensity(0));
      }
    TEST_F(EnviromentTest, Calculate_Density_11000_m) {
          ASSERT_EQ(0.3639,atmosphere.getDensity(11000));
      }
    TEST_F(EnviromentTest, Calculate_Density_20000_m) {
          ASSERT_EQ(0.0880,atmosphere.getDensity(20000));
     }

    TEST_F(EnviromentTest, Calculate_Density_32000_m) {
          ASSERT_EQ(0.0132,atmosphere.getDensity(32000));
    }
    TEST_F(EnviromentTest, Calculate_Density_47000_m) {
        ASSERT_EQ(0.0014,atmosphere.getDensity(47000));
    }

    TEST_F(EnviromentTest, Calculate_Density_51000_m) {
        ASSERT_EQ(0.0008,atmosphere.getDensity(51000));
    }

    TEST_F(EnviromentTest, Calculate_Density_71000_m) {
        ASSERT_EQ(0.0002,atmosphere.getDensity(71000));
    }

    TEST_F(EnviromentTest, Calculate_Density_80000_m) {
        ASSERT_EQ(1.9E-5,atmosphere.getDensity(80000));
    }

} // namespace
