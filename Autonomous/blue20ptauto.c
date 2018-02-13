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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void baseControl(int leftPower, int rightPower)
{
	motor[leftSideDrive] = leftPower;
	motor[rightSideDrive] = rightPower;
}

void liftControl (int leftLift, int rightLift)
{
	motor[leftMobileGoal] = leftLift;
	motor[rightMobileGoal] = rightLift;
}

task main ()
{
	int forwards;
	int backwards;
	int nada;

	forwards = 127;
	backwards = -127;
	nada = 0;
liftControl(127, 127);
wait1Msec(.25);
baseControl(123, forwards);
wait1Msec(1350);
}
