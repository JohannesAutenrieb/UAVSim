#include<iostream>
#include<stdio.h>
#include<string>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include"terminalwindow.h"
#include"FlightVehicle/Multicopter.hpp"
#include"FlightDynamic/FlightDynamic.hpp"

#include"Thread/Worker.hpp"

#include "pugixml.hpp"


int main(int argc, char *argv[])
{
    // Initialization of the USB-Serialbus device
    system("sudo stty -F /dev/ttyUSB0 921600 cs8 -cstopb -parenb -ixoff");

    //taking execution parameter and store it in string
    std::string xml_name(argv[1]);
    std::string relativ_path_to_xml("../../FlightVehicleData/");

    //parameter for xml parsing
    if(argc > 1)
    {
        std::cout<<"!!!! Simulation has been succesfully started! Simulation is loading following XML-File: "<<xml_name<<endl;
        relativ_path_to_xml.append(xml_name);   //put xml-name and xml-path together
        std::cout<<"The XML-File is laying in:"<<relativ_path_to_xml<<endl;
    }
    else
    {
        std::cerr<<"!!!!! ERROR: No XML FILE GIVEN TO SIMULATION!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return (0);
    }
    //starting the Qt Application
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    // creating multicopter object
    Multicopter multicopter(relativ_path_to_xml);
    FlightDynamic flight_dynamic(multicopter);


    //initalization worker thread for calculation
    Worker timer(flight_dynamic, relativ_path_to_xml);

    QIcon appIcon;
    appIcon.addFile(":/Icons/Kaist");
    appIcon.addFile(":/Icons/Kaist");
    app.setWindowIcon(appIcon);

    //Main Window which is starting the simualation
    MainWindow mainWindow(timer, flight_dynamic, multicopter);
    mainWindow.show();

    return app.exec();
}
