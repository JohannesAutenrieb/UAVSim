#ifndef TERMINALWINDOW_H
#define TERMINALWINDOW_H

#include <QDialog>
#include<QThread>
#include<QTimer>
#include <QCloseEvent>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include"FlightDynamic/FlightDynamic.hpp"

namespace Ui {
class TerminalWindow;
}

class TerminalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TerminalWindow(FlightDynamic &flight_dynamic,QWidget *parent = 0);
    ~TerminalWindow();
    QTimer *displaytimer;
public slots:
    void display();
    virtual void reject();
signals:
    void finished();
    void error(QString err);
private:
    Ui::TerminalWindow *ui;
    FlightDynamic &flight_dynamic;
    string  aileron;
    string  elevator;
    string  rudder;
    string  throttle;
    string  x_position;
    string  y_position;
    string  altitude;
    string  pitch;
    string  heading;
    string  roll;



};

#endif // TERMINALWINDOW_H
