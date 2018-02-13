#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mainLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           turntableMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           gripMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftExtension, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)


float Kp = 0.5;
float Ki = 0.2;
float Kd = 0.1;
float error;
float targetvalue;
float sensorReading = SensorValue[RightEncoder})+(SensorValue[LeftEncoder])/2
float integral = integral+error; //



while(time1[T1]<=15000)
{
	error = (targetvalue) - (sensorReading);
	integral = integral + error;

	if(error = 0)
	{
		integral = 0;
	}

	if(abs(error)>40)
	{
		integral = 0;
	}
	derivitive = error - previouserror

	previous_error = error;

	speed = (Kp*error) + (Ki*integral) + (Kd*deritive);
}


task main()
{



}
