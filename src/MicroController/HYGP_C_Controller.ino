#include <Wire.h>
#include <avr/interrupt.h>

#include "Messages.h"
#include "DataStructure.h"
#include "SensorInspection.h"
#include "ReceiverTransmitter.h"
#include "PWMOut.h"
#include "Filters.h"
#include "Controller.h"

#include "Macros.h"

unsigned short keyInput;

struct _Flags Flags;
struct _Sensor Sensor;
struct _Motor Motor;
struct PCONCAT_(, GYRO_MODEL) GYRO_MODEL;
struct _Controller Controller;

const float systemFreq = 200;  
const int systemPeriod = 5000; // (1/systemFreq) [us, microseconds]

char str[80];
volatile unsigned long systemTimer; 
volatile unsigned long setupTimer; 
volatile unsigned long stanbyTimer;
volatile unsigned long receiverTimer0; 
volatile unsigned long receiverTimer1, receiverTimer2, receiverTimer3, receiverTimer4; 
volatile unsigned long motorTimer0; /
volatile unsigned long motorTimer1, motorTimer2, motorTimer3, motorTimer4; 

void ReadADC0();

void setup() {
  //![0] put your setup code here, to run once:
  pinMode(2, OUTPUT); //LED RED
  pinMode(12, OUTPUT); //LED YELLOW
  pinMode(13, OUTPUT); //LED GREEN

  //![1] EEPROM
// TBD


  //Baudrate 57600
  //Serial.begin(57600);

  //Two Wire Bit Rate Register, TWBR = ((cpu freq./twi freq.) - 16) / 2
#if F_CPU == 16000000L
  Flags.mainFrequencyCheck = 1;
#else
  Flags.mainFrequencyCheck = 0;
#endif
  Wire.begin();
  TWBR = 12; //twi freq.400kHz( cpu freq. 16000000L, twi freq. 100000L)


  cli();
  PCICR |= (1 << PCIE0);    // B (PCINT0 - PCINT7, 8-13) 
  PCMSK0 |= (1 << PCINT0);  // (PCINT0, 8)
  PCMSK0 |= (1 << PCINT1);  // (PCINT1, 9)
  PCMSK0 |= (1 << PCINT2);  // (PCINT2, 10)
  PCMSK0 |= (1 << PCINT3);  // (PCINT3, 11)
  sei();

  //DDRD |= B00111100; (0b00000000 gcc)
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);


    Flags.flightMode = 0;
  
    Sensor.Battery.scaler = 0.014648; // [5V / 1024setps * 3], 3 = (R1+R2)/(R1)
    Sensor.Battery.batteryVoltage = 11.0f; 
    
    Motor.outputPWM1 = PWM_LOW;
    Motor.outputPWM2 = PWM_LOW;
    Motor.outputPWM3 = PWM_LOW;
    Motor.outputPWM4 = PWM_LOW;
    
    Sensor.Receiver.channel1Center = 1500;
    Sensor.Receiver.channel2Center = 1500;
    Sensor.Receiver.channel3Center = 1500;
    Sensor.Receiver.channel4Center = 1500;
    Sensor.Receiver.channel1Min = 1000;
    Sensor.Receiver.channel2Min = 2000;
    Sensor.Receiver.channel3Min = 1000;
    Sensor.Receiver.channel4Min = 1000;
    Sensor.Receiver.channel1Max = 2000;
    Sensor.Receiver.channel2Max = 1000;
    Sensor.Receiver.channel3Max = 2000;
    Sensor.Receiver.channel4Max = 2000;

    Sensor.Receiver.deadBand = 8;

    Controller.pRateGain[0] = 1.1; //P Roll
    Controller.pRateGain[1] = 0.02; //I
    Controller.pRateGain[2] = 1; //D
    Controller.qRateGain[0] = 1.1; //P Pitch
    Controller.qRateGain[1] = 0.02; //I
    Controller.qRateGain[2] = 1; //D
    Controller.rRateGain[0] = 4.5; //P Yaw
    Controller.rRateGain[1] = 0.05; //I
    Controller.rRateGain[2] = 0; //D
  
  while((Sensor.Battery.batteryVoltage<11.1) || 
        (Sensor.Receiver.channel1Input <= 0) ||
        (Sensor.Receiver.channel1Input > 2000) ||
        (Sensor.Receiver.channel3Input > Sensor.Receiver.channel3Min))
  {
    ReadADC0(); 
    /*
Serial.print(Sensor.Battery.batteryVoltage);
Serial.print(F(" "));
Serial.print(Sensor.Receiver.channel1Input);
Serial.print(F(" "));
Serial.println(Sensor.Receiver.channel3Input);
*/
    delay(100);
    digitalWrite(2,HIGH);
//TBD: digitalWrite(2,HIGH);
  }
//TBD: digitalWrite(#,LOW);
    digitalWrite(2,LOW);


  
  digitalWrite(12,HIGH);
  FUNCTION_(GYRO_MODEL, Init)();
  delay(5000);
  FUNCTION_(GYRO_MODEL, CalibGyro)();

  digitalWrite(12,LOW);


  digitalWrite(12,HIGH);
  setupTimer = millis() + 3000;
  while(setupTimer > millis())
  {
    PWMOutRaiser();
    PWMOutFaller();
  }
  
  Motor.outputPWM1 = 1150;
  setupTimer = millis() + 500;
  while(setupTimer > millis())
  {
    PWMOutRaiser();
    PWMOutFaller();
  }
  Motor.outputPWM1 = PWM_LOW;
  Motor.outputPWM2 = 1150;
  setupTimer = millis() + 500;
  while(setupTimer > millis())
  {
    PWMOutRaiser();
    PWMOutFaller();
  }
  Motor.outputPWM2 = PWM_LOW;
  Motor.outputPWM3 = 1150;
  setupTimer = millis() + 500;
  while(setupTimer > millis())
  {
    PWMOutRaiser();
    PWMOutFaller();
  }
  Motor.outputPWM3 = PWM_LOW;
  Motor.outputPWM4 = 1150;
  setupTimer = millis() + 500;
  while(setupTimer > millis())
  {
    PWMOutRaiser();
    PWMOutFaller();
  }
  Motor.outputPWM4 = PWM_LOW;
  setupTimer = millis() + 3000;
  while(setupTimer > millis())
  {
    PWMOutRaiser();
    PWMOutFaller();
  }
  digitalWrite(12,LOW);

//TBD: LED(11.4v) -> (10.8v) voltage indicator
  digitalWrite(13,HIGH);

  //MessageWelcome();
  //delay(1000);
  //MessageMenu();
  
//UNCOMMENT TO TEST SETUP ONLY
  //while(1);

  //![#] 
  


  FUNCTION_(GYRO_MODEL, ReadData)();
  FUNCTION_(GYRO_MODEL, TransferData)();
  FUNCTION_(GYRO_MODEL, LPF)();
  EulerEstimator();
  Sensor.Estimates.roll = Sensor.Estimates.rollFromAcc; 
  Sensor.Estimates.pitch = Sensor.Estimates.pitchFromAcc; 
    
}

void loop() 
{
//  Serial.print(F(">>>>>>[안내] gR = "));
//  Serial.print(Sensor.Estimates.rollFromGyro);
//  Serial.print("\t");
/*
  Serial.print(F("gP = "));
  Serial.println(Sensor.Estimates.pitchFromGyro);
  */
//  Serial.print("\t");
//  Serial.print(F("aR = "));
//  Serial.print(Sensor.Estimates.rollFromAcc);
//  Serial.print("\t");
//  Serial.print(F("aP = "));
//  Serial.print(Sensor.Estimates.pitchFromAcc);
//  Serial.print("\t");
//  Serial.print(F("R = "));
//  Serial.print(Sensor.Estimates.roll);
//  Serial.print(F("P = "));
//  Serial.println(Sensor.Estimates.pitch);

  FUNCTION_(GYRO_MODEL, ReadData)();
  FUNCTION_(GYRO_MODEL, TransferData)();
  FUNCTION_(GYRO_MODEL, LPF)();
  EulerEstimator();
  StickNormalize();

// TBD: Switch-Case 로 대체
  if(Flags.flightMode < 0)
  {
    Flags.flightMode++;
  }
  
  if((Flags.flightMode == 0) &&
     (Sensor.Receiver.channel3 == 1000) && 
     (Sensor.Receiver.channel2 == 2000) &&
     ((Sensor.Receiver.channel1 == 1000)||(Sensor.Receiver.channel1 == 2000)))
  {
    Motor.outputPWM1 = 1150;
    Motor.outputPWM2 = 1150;
    Motor.outputPWM3 = 1150;
    Motor.outputPWM4 = 1150;
    Flags.flightMode = 2;
  }

  if((Flags.flightMode == 1) && (stanbyTimer + 1000 < millis()) &&
     (Sensor.Receiver.channel3 == 1000) && 
     (Sensor.Receiver.channel2 == 2000) &&
     ((Sensor.Receiver.channel1 == 1000)||(Sensor.Receiver.channel1 == 2000)))
  {
    Motor.outputPWM1 = PWM_LOW;
    Motor.outputPWM2 = PWM_LOW;
    Motor.outputPWM3 = PWM_LOW;
    Motor.outputPWM4 = PWM_LOW;
    Flags.flightMode = -systemFreq*2;
  }

  if((Flags.flightMode == 1) && (stanbyTimer + 3000 < millis()))
  {
    Motor.outputPWM1 = PWM_LOW;
    Motor.outputPWM2 = PWM_LOW;
    Motor.outputPWM3 = PWM_LOW;
    Motor.outputPWM4 = PWM_LOW;
    Flags.flightMode = 0;
  }
  
  if((Flags.flightMode == 2) && (Sensor.Receiver.channel3 <= 1020))
  {
    Motor.outputPWM1 = 1150;
    Motor.outputPWM2 = 1150;
    Motor.outputPWM3 = 1150;
    Motor.outputPWM4 = 1150;
    
    Controller.pAccumulatedError = 0;
    Controller.qAccumulatedError = 0;
    Controller.rAccumulatedError = 0;
    Controller.pPreviousError = 0;
    Controller.qPreviousError = 0;
    Controller.rPreviousError = 0;

    stanbyTimer = millis();
    Flags.flightMode = 1;
  }

  if(((Flags.flightMode == 1) || (Flags.flightMode == 2)) && 
     (Sensor.Receiver.channel3 > 1020))
  {
    Flags.flightMode = 3;
  }

  if(Flags.flightMode == 3)
  {
    PIDController();
    Motor.outputPWM1 = Controller.zDotCommand + Controller.pCommand - Controller.qCommand - Controller.rCommand;
    Motor.outputPWM2 = Controller.zDotCommand - Controller.pCommand - Controller.qCommand + Controller.rCommand;
    Motor.outputPWM3 = Controller.zDotCommand - Controller.pCommand + Controller.qCommand - Controller.rCommand;
    Motor.outputPWM4 = Controller.zDotCommand + Controller.pCommand + Controller.qCommand + Controller.rCommand;

    /* [OPTIONAL] BATTERY COMPENSATION */
    //Motor.outputPWM1 += Motor.outputPWM1 * (12.6f - Sensor.Battery.batteryVoltage) / 1.5 / 10; //11.1V 
    //
    //
    /*
    Motor.outputPWM1 += Motor.outputPWM1 * (12.6f - Sensor.Battery.batteryVoltage) / 1.5 / 10;
    Motor.outputPWM2 += Motor.outputPWM2 * (12.6f - Sensor.Battery.batteryVoltage) / 1.5 / 10;
    Motor.outputPWM3 += Motor.outputPWM3 * (12.6f - Sensor.Battery.batteryVoltage) / 1.5 / 10;
    Motor.outputPWM4 += Motor.outputPWM4 * (12.6f - Sensor.Battery.batteryVoltage) / 1.5 / 10;
    */
  }
  
  if((Flags.flightMode == 3) && (Sensor.Receiver.channel3 <= 1020))
  {
    Flags.flightMode = 2;
  }

  if((micros() - systemTimer > systemPeriod))
  {
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(2,HIGH);
  }

  
  PWMOutRaiser(); //systemTimer
  
  // Raiser 
  Faller 
  1ms 
  
  ReadADC0();

  PWMOutFaller();

  // 400Hz.5ms, 200Hz 2ms 
}


ISR (PCINT0_vect) // Port B, PCINT0 - PCINT7: Handle pin change interrupt from 8 to 13.
{
  //![0]
  receiverTimer0 = micros();


  if (PINB & (1 << PB0)) //  Rising
  {
    if (Flags.pin8 == 0) // Low high
    {
      receiverTimer1 = receiverTimer0;
      Flags.pin8 = 1;
    }
  }
  else // Falling
  {
    if (Flags.pin8 == 1) // Highlow  (duty cycle)
    {
      Flags.pin8 = 0;
      Sensor.Receiver.channel1Input = receiverTimer0 - receiverTimer1;
    }
  }

  //![2] 9, PB1, 2
  if (PINB & (1 << PB1)) // Rising
  {
    if (Flags.pin9 == 0) // Low high
    {
      receiverTimer2 = receiverTimer0;
      Flags.pin9 = 1;
    }
  }
  else //  Falling
  {
    if (Flags.pin9 == 1) // High low (duty cycle)
    {
      Flags.pin9 = 0;
      Sensor.Receiver.channel2Input = receiverTimer0 - receiverTimer2;
    }
  }

  //![3] 10, PB2, 3
  if (PINB & (1 << PB2)) //  Rising
  {
    if (Flags.pin10 == 0) // low high
    {
      receiverTimer3 = receiverTimer0;
      Flags.pin10 = 1;
    }
  }
  else // 10번핀 Falling인 경우
  {
    if (Flags.pin10 == 1) // High low (duty cycle)
    {
      Flags.pin10 = 0;
      Sensor.Receiver.channel3Input = receiverTimer0 - receiverTimer3;
    }
  }

  //![4] 11, PB3
  if (PINB & (1 << PB3)) // 11 Rising
  {
    if (Flags.pin11 == 0) // Low high
    {
      receiverTimer4 = receiverTimer0;
      Flags.pin11 = 1;
    }
  }
  else // 11 Falling
  {
    if (Flags.pin11 == 1) // High low (duty cycle)
    {
      Flags.pin11 = 0;
      Sensor.Receiver.channel4Input = receiverTimer0 - receiverTimer4;
    }
  }
}
ISR(PCINT1_vect) {}   // Port C, PCINT8 - PCINT14
ISR(PCINT2_vect) {}   // Port D, PCINT16 - PCINT23

void ReadADC0()
{
  Sensor.Battery.mainBatteryVoltageInput = analogRead(0);
  
  Sensor.Battery.batteryVoltage = (0.9 * Sensor.Battery.batteryVoltage + 
                                   0.1 * ((float)Sensor.Battery.mainBatteryVoltageInput * Sensor.Battery.scaler + 0.8318));
  //Low pass filter. 0.8318 1N4007 
}
