/**
 *
 * File: Worker.cpp
 * Class name: Worker
 * Purpose: This Class is manaeging the thread and the timer to trigger the discret function call
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/


#include"Worker.hpp"

#include<iostream>


Worker::Worker(FlightDynamic &flightdynamic, const std::string &relativ_path_to_xml):
flightDynamics(flightdynamic)
{
    /*This Part initialze the Thread as a Timer*/

    //loading of xml
     pugi::xml_document doc;
     std::stringstream ss;
     pugi::xml_parse_result result = doc.load_file(relativ_path_to_xml.c_str());
     std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
     pugi::xml_node multicoper_data = doc.child("Multicopter").child("General");

     //reading the variables and write them in to the attributes
     ss<<multicoper_data.child_value("simulation_frequenzy");
     ss>>frequency;
     ss.str("");
     computing_time=(1/frequency);
     cout<<"!!Computing Time: %d\n"<<computing_time<<endl;
     cout<<"!!Frequency: %d\n"<<frequency<<endl;
     int    time_in_ms = computing_time*1000;

    //creating qt timer thread
    timer = new QTimer(this);

    //connecting timer thread with target process
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->setInterval(time_in_ms);

}

Worker::~Worker() {

}
/**
 * Method description:          This function is been triggerd by the timer and executing in discret timespans itselfs
 * @return void                 description:-
 * @since 15.06.2017
 * @author Johannes Autenrieb
 */

void Worker::process()
{
    //timer print out for debuging
    qDebug() << "Timer...";
    cout<<"!!Computing Time:"<<computing_time<<endl;
    cout<<"!!Frequency:"<<frequency<<endl;

    //reading the input from the Futuba GCS
    serialreader.listen();

    printf("!!!! THREAD::: AILERON\n");
    printf("Aileron: %hu",serialreader.getAileron());

    //call of flight dynamic calculation function
    flightDynamics.calculation(computing_time,serialreader.getElevator(),serialreader.getAileron(),serialreader.getRudder(),serialreader.getThrottle());
    emit finished();
}
/**
 * Method description:          This function is starting the thread calculation
 * @return void                 description:-
 * @since 15.06.2017
 * @author Johannes Autenrieb
 */

void    Worker::startTimer()
{
    timer->start();
}


void    Worker::stopTimer()
{
    timer->stop();
}
