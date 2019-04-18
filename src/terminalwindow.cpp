#include "terminalwindow.h"
#include "ui_terminalwindow.h"

TerminalWindow::TerminalWindow(FlightDynamic &flight_dynamic, QWidget *parent) :
    QDialog(parent),
    flight_dynamic(flight_dynamic),
    ui(new Ui::TerminalWindow)
{
    ui->setupUi(this);

    //creating qt timer thread
    displaytimer = new QTimer(this);
    int time_in_ms=1;
    //connecting timer thread with target process
    connect(displaytimer, SIGNAL(timeout()), this, SLOT(display()));
    displaytimer->setInterval(time_in_ms);
    displaytimer->start();

}

TerminalWindow::~TerminalWindow()
{
    delete ui;
}
void TerminalWindow::display()
{
    //control input
      aileron=boost::lexical_cast<string>(flight_dynamic.flightMode.controlInput.aileron);
      elevator=boost::lexical_cast<string>(flight_dynamic.flightMode.controlInput.elevator);
      rudder=boost::lexical_cast<string>(flight_dynamic.flightMode.controlInput.rudder);
      throttle=boost::lexical_cast<string>(flight_dynamic.flightMode.controlInput.throttle);

      ui->aileron_control_input_lineEdit->setText(aileron.c_str());
      ui->rudder_control_input_lineEdit->setText(rudder.c_str());
      ui->throttle_control_input_lineEdit->setText(throttle.c_str());
      ui->elevator_control_input_lineEdit->setText(elevator.c_str());

      //position of the multicopter
      x_position=boost::lexical_cast<string>(flight_dynamic.flightMode.position.x);
      y_position=boost::lexical_cast<string>(flight_dynamic.flightMode.position.y);
      altitude=boost::lexical_cast<string>(flight_dynamic.flightMode.position.altitude);

      ui->x_position_lineEdit->setText(x_position.c_str());
      ui->y_position_lineEdit->setText(y_position.c_str());
      ui->alititude_position_lineEdit->setText(altitude.c_str());

      //attitude of the multicopter
      pitch=boost::lexical_cast<string>(flight_dynamic.flightMode.attitude.theta);
      heading=boost::lexical_cast<string>(flight_dynamic.flightMode.attitude.psi);
      roll=boost::lexical_cast<string>(flight_dynamic.flightMode.attitude.phi);

      ui->heading_alignment_lineEdit->setText(heading.c_str());
      ui->pitch_alignment_lineEdit->setText(pitch.c_str());
      ui->roll_alignment_lineEdit->setText(roll.c_str());
}

void TerminalWindow::reject()
{

}

