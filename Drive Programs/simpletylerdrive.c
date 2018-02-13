#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mainLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           turntableMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           gripMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftExtension, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void liftControl (int leftLift, int rightLift)
{
	motor[leftMobileGoal] = leftLift;
	motor[rightMobileGoal] = rightLift;
}


// If button up (StartTask Mogo up & Stop Task MogoDown)
// If bottom down (StartTask Mogo Down & Stop Task MogoUp
//


task main()
{

	while(1==1)
	{
		motor[leftSideDrive] = vexRT[Ch3];
		motor[rightSideDrive] = vexRT[Ch2];

		if(vexRT[Btn6U] == 1)
		{
			liftControl(-127, -127);
		}
		else if(vexRT[Btn6D] == 1)
		{
			liftControl(127, 127,);
		}
		else
		{
liftControl(0, 0);
		}
		if(vexRT[Btn6D] == 1)
		{
			liftControl(127, 127);
		}
		else if(vexRT[Btn6U] == 1)
		{
		liftControl(-127, -127);
		}
		else
		{
		liftControl(0, 0);
		}
	}
}