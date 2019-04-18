#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QScopedPointer>
#include"terminalwindow.h"
#include"Thread/Worker.hpp"
#include"FlightDynamic/FlightDynamic.hpp"
#include"FlightVehicle/Multicopter.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Worker &thread, FlightDynamic &flight_dynamic,Multicopter &multicopter, QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    void start();

private:
    QScopedPointer<Ui::MainWindow> ui;
    TerminalWindow terminal;
    Worker          &thread;
    FlightDynamic   &flight_dynamic;
    Multicopter     &multicopter;
};

#endif
