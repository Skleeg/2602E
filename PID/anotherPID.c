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

void moveBase (int speed)
{
		motor[leftSideDrive] = speed;
		motor[rightSideDrive] = speed;
}

	float Kp = 0.2;
	float Ki = 0.05;
float error;
float power;
int integral;

void myPID(int setpoint)
{
	while(time1[T1] < 15000)
	{
		error = setpoint - sensor value;
			integral = integral + error;
			if(error == 0 //or passes setpoint/)
			{
				integral = 0;
			}
			if(error >= //something higher than useful)
			{
				integral = 0;
			}
				deritive = error - PrevError;
				prevError = error;
		power = (error*kP) + (integral*kI);
		wait1Msec(0.15);
	}
	moveBase(0);
}

task main()
{
clearTimer(T1);


}
