/**
 * Model the atmosphere in a way consistent with the laws
 * of physics.
 *
 * Each instance of this class models a particular air mass.
 * You may freely move up, down, or sideways in the air mass.
 * In contrast, if you want to compare different air masses,
 * you should use a separate instance for each one.
 *
 */

#ifndef _ATMOSPHERE_HXX
#define _ATMOSPHERE_HXX

#define NUMBER_OF_LAYERS 8
#define NUMBER_OF_ENVIROMENT_VARIABLES_IN_LAYER 9


class ISA_layer {
public:
  double height;
  double temp;
  double pressure;
  double lapse;
  double density;
  ISA_layer(int, double h, double, double p, double, double t, double,
                    double l=-1, double=0, double d=0)
   :  height(h),        // [meters]
      temp(t),          // [kelvin]
      pressure(p),      // [Pa]
      lapse(l),         // [K/m]
      density(d)
  {}
};

extern const ISA_layer ISA_def[];


class Atmosphere {

    public:
      Atmosphere();
      void calculate(double altitude);
      double getTemperature(double altitude);
      void setTemperature(double value);
      double getPressure(double altitude);
      void setPressure(double value);
      double getDensity(double altitude);
      void setDensity(double value);
      double getSoundspeed();
      void setSoundspeed(double value);
      double getDynamicViscosity();
      void setDynamicViscosity(double value);
      double getKinematicViscosity();
      void setKinematicViscosity(double value);

    private:
      double lapse;
      double temperature;
      double pressure;
      double density;
      double soundspeed;
      double dynamicViscosity;
      double kinematicViscosity;
      double viscosity;
      double SutherlandConstant;
      double Beta;

};



#endif // _ATMOSPHERE_HXX
