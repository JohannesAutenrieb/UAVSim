#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Worker &thread, FlightDynamic &flight_dynamic, Multicopter &multicopter, QWidget *parent)
: QMainWindow(parent),
  thread(thread),
  terminal(flight_dynamic, this),
  flight_dynamic(flight_dynamic),
  multicopter(multicopter),
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
}

void MainWindow::start()
{
    flight_dynamic=FlightDynamic(multicopter);
    thread.startTimer();
    terminal.exec();
    thread.stopTimer();
}
