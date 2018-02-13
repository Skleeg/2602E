#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mainLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           turntableMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           gripMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftExtension, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)
task main()
{
	int forwards;
	int backwards;
	int nada;

	forwards = 127;
	backwards = -127;
	nada = 0;..............................................................................................................................
while (true)
	{
		motor[rightSideDrive] = vexRT[Ch2];
		motor[leftSideDrive] = vexRT[Ch3];
		motor[turntableMotor] = vexRT[Ch4Xmtr2];

		if(vexRT[Btn8LXmtr2] == 1)
		{
			motor[liftExtension] = forwards;
			motor[mainLift] = forwards;
		}
		else if(vexRT[Btn8DXmtr2] == 1)
		{
			motor[liftExtension] = backwards;
			motor[mainLift] = backwards;
		}
		else
		{
			motor[liftExtension] = nada;
			motor[mainLift] = nada;
		}
		if(vexRT[Btn5UXmtr2] == 1)
		{
			motor[rightMobileGoal] = forwards;
			motor[leftMobileGoal] = forwards;
		}
		else if(vexRT[Btn5DXmtr2] == 1)
		{
			motor[rightMobileGoal] = backwards;
			motor[leftMobileGoal] = backwards;
		}
		else
		{
			motor[rightMobileGoal] = nada;
			motor[leftMobileGoal] = nada;
		}
		if(vexRT[Btn6UXmtr2] == 1)
		{
			motor[gripMotor] = forwards;
		}
		else if(vexRT[Btn6DXmtr2] == 1)
		{
			motor[gripMotor] = backwards;
		}
		else
		{
			motor[gripMotor] = nada;
		}
	}
}
