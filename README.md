# UAVSim

```diff
- # System is still in experimental and not fully working
```

This project is working on a generic and parameterized multicopter simulation enviroment, written  in the C++ language. The software system has interfaces to be controlled by ground station systems via implementation of the MAVLink protocol. Further more is the DIS Standard implemented in order to enable the possiblty to participate in a distributed muliplayer flight simulation.

The system is able to read out inputs from a RC flight controler modul through the serial port. Therfore it is possible to control a simulated UAV with a manual UAV controller.

#### System Architecture

The “UAVsim”-Project is developed as a modularised software system. The distinguable features of the simulation are divided in to different packages which all are focusing on specific features which needs to be provided.

### Usage

The system is developed under Ubuntu 16.04.1 LTS and uses FrSky modules for the interaction with a remot controller.

#### This application is using the following libraries:

* [Qt5](https://wiki.qt.io/Main)
* [Plib](http://plib.sourceforge.net/whats_inside.html)
* [OpenGl](https://www.opengl.org/)
* [Boost](https://www.boost.org/)
* [Google Test](https://github.com/google/googletest)
* [MavLink](https://github.com/mavlink)
* [Open-DIS](https://github.com/open-dis)

