/**
 *
 * File: Worker.cpp
 * Class name: Worker
 * Purpose: This Class is manaeging the thread and the timer to trigger the discret function call
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/
#ifndef _WORKER_HXX
#define _WORKER_HXX

#include<QThread>
#include <QString>
#include<QTimer>
#include<QDebug>
#include"../../lib/pugixml/pugixml.hpp"
#include"../Communication/SerialPortReader.hpp"

#include"../FlightDynamic/FlightDynamic.hpp"
class Worker : public QObject {
    Q_OBJECT
public:
    Worker(FlightDynamic &flightdynamic, const std::string &relativ_path_to_xml);
    ~Worker();
    QTimer *timer;
public slots:
    void process();
    void startTimer();
    void stopTimer();
signals:
    void finished();
    void error(QString err);
private:
    FlightDynamic &flightDynamics;
    SerialPortReader serialreader;
    double computing_time;
    double    frequency;
};

#endif // _WORKER_HXX
