#pragma config(Sensor, dgtl1,  testTouch1,     sensorTouch)
#pragma config(Sensor, dgtl2,  testTouch2,     sensorTouch)
#pragma config(Sensor, dgtl3,  testTouch3,     sensorTouch)
#pragma config(Sensor, dgtl4,  testTouch4,     sensorTouch)
#pragma config(Sensor, dgtl5,  testTouch5,     sensorTouch)
#pragma config(Sensor, dgtl6,  testTouch6,     sensorTouch)
#pragma config(Sensor, dgtl7,  testTouch7,     sensorTouch)
#pragma config(Sensor, dgtl8,  testTouch8,     sensorTouch)
#pragma config(Sensor, dgtl9,  testTouch9,     sensorTouch)
#pragma config(Sensor, dgtl10, testTouch10,    sensorTouch)
#pragma config(Sensor, dgtl11, testTouch11,    sensorTouch)
#pragma config(Sensor, dgtl12, testTouch12,    sensorTouch)
#pragma config(Motor,  port1,           testMotor1,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,           testMotor2,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           testMotor3,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           testMotor4,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           testMotor5,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           testMotor6,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           testMotor7,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           testMotor8,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           testMotor9,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          testMotor10,   tmotorServoContinuousRotation, openLoop)

//Plug up to ten motors in any port, and 12 bumper/limit switches in any digital port.

int motorSpeed = 0;
bool pressed = false;




task main()
{

  while(true)
  {

    if(SensorValue(testTouch1) == 1)
    	pressed = true;
    else if(SensorValue(testTouch2) == 1)
      pressed = true;
    else if(SensorValue(testTouch3) == 1)
      pressed = true;
    else if(SensorValue(testTouch4) == 1)
      pressed = true;
    else if(SensorValue(testTouch5) == 1)
      pressed = true;
    else if(SensorValue(testTouch6) == 1)
      pressed = true;
    else if(SensorValue(testTouch7) == 1)
      pressed = true;
    else if(SensorValue(testTouch8) == 1)
      pressed = true;
    else if(SensorValue(testTouch9) == 1)
      pressed = true;
    else if(SensorValue(testTouch10) == 1)
      pressed = true;
    else if(SensorValue(testTouch11) == 1)
      pressed = true;
    else if(SensorValue(testTouch12) == 1)
      pressed = true;
    else
    pressed = false;


   if(pressed == true)
    motorSpeed = 127;
   else
     motorSpeed = 0;


  	motor[testMotor1] = motorSpeed;
  	motor[testMotor2] = motorSpeed;
  	motor[testMotor3] = motorSpeed;
  	motor[testMotor4] = motorSpeed;
  	motor[testMotor5] = motorSpeed;
  	motor[testMotor6] = motorSpeed;
  	motor[testMotor7] = motorSpeed;
  	motor[testMotor8] = motorSpeed;
  	motor[testMotor9] = motorSpeed;
  	motor[testMotor10] = motorSpeed;
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
