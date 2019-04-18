#include "Controller.h"

void StickNormalize()
{
//TBD: REVERSE 
//TBD: 1080~1500~1920 Normalize.
  Sensor.Receiver.channel1 =  (Sensor.Receiver.channel1Input - Sensor.Receiver.channel1Center) + 1500;
  Sensor.Receiver.channel2 =  (Sensor.Receiver.channel2Input - Sensor.Receiver.channel2Center) + 1500; //Stick Pull
  Sensor.Receiver.channel3 =  (Sensor.Receiver.channel3Input - Sensor.Receiver.channel3Center) + 1500; //REVERSED (Stick Pull)
  Sensor.Receiver.channel4 =  (Sensor.Receiver.channel4Input - Sensor.Receiver.channel4Center) + 1500;
}

void PIDController()
{
  Controller.pReference = (Sensor.Receiver.channel1 >= (1500 + Sensor.Receiver.deadBand))?
                          (Sensor.Receiver.channel1 - (1500 + Sensor.Receiver.deadBand)):
                          ((Sensor.Receiver.channel1 <= 1500 - Sensor.Receiver.deadBand)?
                           (Sensor.Receiver.channel1 - (1500 - Sensor.Receiver.deadBand)):(0)); //[-412 ~ 0 ~ 412]
  Controller.qReference = (Sensor.Receiver.channel2 >= (1500 + Sensor.Receiver.deadBand))?
                          (Sensor.Receiver.channel2 - (1500 + Sensor.Receiver.deadBand)):
                          ((Sensor.Receiver.channel2 <= 1500 - Sensor.Receiver.deadBand)?
                           (Sensor.Receiver.channel2 - (1500 - Sensor.Receiver.deadBand)):(0)); //[-412 ~ 0 ~ 412]
  Controller.rReference = (Sensor.Receiver.channel4 >= (1500 + Sensor.Receiver.deadBand))?
                          (Sensor.Receiver.channel4 - (1500 + Sensor.Receiver.deadBand)):
                          ((Sensor.Receiver.channel4 <= 1500 - Sensor.Receiver.deadBand)?
                           (Sensor.Receiver.channel4 - (1500 - Sensor.Receiver.deadBand)):(0)); //[-412 ~ 0 ~ 412]
                           
  Controller.pReference /= 4; // [-103 ~ 0 ~ 103 deg/s command ref. from pilot]
  Controller.qReference /= 4; // aggressive
  Controller.rReference /= 4;

  /*Pilot assistance using Euler Angle
  Controller.pReference -= Sensor.Estimates.roll; // Pilot assistance
  Controller.qReference -= Sensor.Estimates.pitch;//
  */

  Controller.pError = (Sensor.Gyro.pFiltered - Controller.pReference);
  Controller.qError = (Sensor.Gyro.qFiltered - Controller.qReference);
  Controller.rError = (Sensor.Gyro.rFiltered - Controller.rReference);

  Controller.pAccumulatedError += Controller.pError;
  Controller.qAccumulatedError += Controller.qError;
  Controller.rAccumulatedError += Controller.rError;

  Controller.pAccumulatedError = (Controller.pAccumulatedError > 400)? (400):
                                  ((Controller.pAccumulatedError < -400)? (-400):(Controller.pAccumulatedError));
  Controller.qAccumulatedError = (Controller.qAccumulatedError > 400)? (400):
                                  ((Controller.qAccumulatedError < -400)? (-400):(Controller.qAccumulatedError));  
  Controller.rAccumulatedError = (Controller.rAccumulatedError > 400)? (400):
                                  ((Controller.rAccumulatedError < -400)? (-400):(Controller.rAccumulatedError));
                                  
  Controller.zDotCommand = (Controller.zDotCommand <= 1800) ? (Sensor.Receiver.channel3 + 70) : 1800; 
  // +70 to make 1150 as a minimum output.
  // pqr control 200. ( 2000) 
  
  Controller.pCommand = (Controller.pRateGain[0] * Controller.pError +
                         Controller.pRateGain[1] * Controller.pAccumulatedError +
                         Controller.pRateGain[2] * (Controller.pError - Controller.pPreviousError)); //dtgain. LP
  Controller.qCommand = (Controller.qRateGain[0] * Controller.qError +
                         Controller.qRateGain[1] * Controller.qAccumulatedError +
                         Controller.qRateGain[2] * (Controller.qError - Controller.qPreviousError));;
  Controller.rCommand = (Controller.rRateGain[0] * Controller.rError +
                         Controller.rRateGain[1] * Controller.rAccumulatedError +
                         Controller.rRateGain[2] * (Controller.rError - Controller.rPreviousError));;

  Controller.pPreviousError = Controller.pError;
  Controller.qPreviousError = Controller.qError;
  Controller.rPreviousError = Controller.rError;

  
}


