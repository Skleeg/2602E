#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mobileGoalMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mainLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           turntableMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           gripMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftExtension, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int forwards;
	int lessforwards;
	int backwards;
	int lessbackwards;
	int nada;


	forwards = 95;
	lessforwards = 85;
	backwards = -95;
	lessbackwards = -85;
	nada = 0;

	SensorValue[RightEncoder] = 0;
	SensorValue[LeftEncoder] = 0;

	//set all sensor values to zero

	while (SensorValue[RightEncoder] > 0)
	//while loop stating that while the value of the right encoder is more than 0, then this code runs

	if (SensorValue[RightEncoder] > (SensorValue[LeftEncoder]))
	{
		motor(rightSideDrive) = lessforwards;
		motor(leftSideDrive) = forwards;
	}
	if (SensorValue[LeftEncoder] > (SensorValue[RightEncoder]))
	{
		motor(leftSideDrive) = lessforwards;
		motor(rightSideDrive) = forwards;
	}
	//code for automatic straigtening for when robot is moving forwards

		while (SensorValue[RightEncoder] < 0)
	//while loop stating that while the value of the front encoder is more than 0, then this code runs

	if (SensorValue[RightEncoder] < (SensorValue[LeftEncoder]))
	{
		motor(rightSideDrive) = lessbackwards;
		motor(leftSideDrive) = backwards;
	}
	if (SensorValue[LeftEncoder] < (SensorValue[RightEncoder]))
	{
		motor(leftSideDrive) = lessbackwards;
		motor(rightSideDrive) = backwards;
	}
}
