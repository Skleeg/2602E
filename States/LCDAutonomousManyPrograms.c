#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightTipper,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftTipper,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "getlcdbuttons.c"

static int MyAutonomous = 0;

//Autonomous Selection

#define MAX_CHOICE 4

void
LcdAutonomousSet( int value, bool select = false )
{
	clearLCDLine(0);
	clearLCDLine(1);

	displayLCDString(1, 0, l_arr_str);
	displayLCDString(1, 13, r_arr_str);

	if(select)
		MyAutonomous = value;

	if( MyAutonomous == value )
		displayLCDString(1, 5, "ACTIVE");
	else
		displayLCDString(1, 5, "Select...");

	switch(value)
	{
	case 0:
		displayLCDString(0, 0, "Ten Point + Tip");
		break;
	case 1:
		displayLCDString(0, 0, "Twenty Point Auto");
		break;
	case 2:
		displayLCDString(0, 0, "Zero Point Auto");
		break;
	case 3:
		displayLCDString(0, 0, "Battery Test");
		break;
	case 4:
		displayLCDString(0, 0, "Defensive");
		break;
	default:
		displayLCDString(0, 0, "Unknown");
		break;
	}
}

//Cycle through different autonomous choices

void
LcdAutonomousSelection()
{
	TControllerButtons button;
	int choice = 0;

	bLCDBacklight = true;

	LcdAutonomousSet(0);

	while( bIfiRobotDisabled )
	{
		button = getLcdButtons();

		if( ( button == kButtonLeft ) || ( button == kButtonRight ) )
		{
			if( button == kButtonLeft )
				if( --choice < 0 ) choice = MAX_CHOICE;

			if( button == kButtonRight )
				if( ++choice > MAX_CHOICE ) choice = 0;
			LcdAutonomousSet(choice);
		}

		if( button == kButtonCenter )
			LcdAutonomousSet( choice, true );

		wait1Msec(10);
	}
}



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	bStopTasksBetweenModes = true;

	LcdAutonomousSelection();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void baseControl(int leftDrive, int rightDrive)
{
	motor[leftSideDrive] = leftDrive;
	motor[rightSideDrive] = rightDrive;
}
void mogoControl(int leftMogo, int rightMogo)
{
	motor[leftMobileGoal] = leftMogo;
	motor[rightMobileGoal] = rightMogo;
}
void tipperControl(int rightTip, int leftTip)
{
	motor[leftTipper] = leftTip;
	motor[rightTipper] = rightTip;
	//nice
}


	task Straighten()
{

int difference;
int leftStart;
int rightStart;


leftStart = 101;
rightStart = 83;


SensorValue(RightEncoder) = 0;
SensorValue(LeftEncoder) = 0;


	while(1 == 1)
	{
		difference = abs(SensorValue(LeftEncoder) - SensorValue(RightEncoder))/1000;

		if(SensorValue(RightEncoder) == SensorValue(LeftEncoder))
		{
			baseControl(leftStart, rightStart);
		}

		if(SensorValue(RightEncoder) > SensorValue(LeftEncoder))
		{
			baseControl(leftStart, (rightStart - difference));
		}

		if(SensorValue(LeftEncoder) > SensorValue(RightEncoder))
		{
			baseControl((leftStart - difference), rightStart);
		}
	}
}


task BackStraighten()
{
float difference;
float leftStart;
float rightStart;


leftStart = -57.5;
rightStart = -47.5;


SensorValue(RightEncoder) = 0;
SensorValue(LeftEncoder) = 0;

	while(1 == 1)
	{

		difference = abs(SensorValue(LeftEncoder) - SensorValue(RightEncoder))/1000;

		if(SensorValue(RightEncoder) == SensorValue(LeftEncoder))
		{
			baseControl(leftStart, rightStart);
		}

		if(SensorValue(RightEncoder) > SensorValue(LeftEncoder))
		{
			baseControl(leftStart, (rightStart - difference));
		}

		if(SensorValue(LeftEncoder) > SensorValue(RightEncoder))
		{
			baseControl((leftStart - difference), rightStart);
		}
	}
}

task BackStraightenFast()
{
float difference;
float leftStart;
float rightStart;


leftStart = -101;
rightStart = -95;


SensorValue(RightEncoder) = 0;
SensorValue(LeftEncoder) = 0;

	while(1 == 1)
	{

		difference = abs(SensorValue(LeftEncoder) - SensorValue(RightEncoder))/1000;

		if(SensorValue(RightEncoder) == SensorValue(LeftEncoder))
		{
			baseControl(leftStart, rightStart);
		}

		if(SensorValue(RightEncoder) > SensorValue(LeftEncoder))
		{
			baseControl(leftStart, (rightStart - difference));
		}

		if(SensorValue(LeftEncoder) > SensorValue(RightEncoder))
		{
			baseControl((leftStart - difference), rightStart);
		}
	}
}
task autonomous()
{
	switch( MyAutonomous )
	{
	case 0:
		//Ten Point + Tip

		startTask(Straighten);
		baseControl(127, 127);
		wait1Msec(3000);
		stopTask(Straighten);

		mogoControl(-127, -127);
		wait1Msec(500);

		startTask(Straighten);
		baseControl(127, 127);
		wait1Msec(500);
		stopTask(Straighten);

		mogoControl(127, 127);
		wait1Msec(500);

		startTask(BackStraightenFast);
		baseControl(-127, -127);
		wait1Msec(1000);
		stopTask(BackStraightenFast);

		baseControl(127, -127);
		wait1Msec(500);

		baseControl(127, 127);
		wait1Msec(1000);

		mogoControl(-127, -127);
		wait1Msec(500);

		baseControl(-127, -127);
		wait1Msec(500);

		baseControl(127, -127);
		wait1Msec(500);

		baseControl(-127, -127);
		wait1Msec(500);

		tipperControl(-127, -127);
		wait1Msec(500);

		baseControl(127, 127);
		wait1Msec(1000);
		break;

	case 1:
		//Twenty Point Auto
		break;

	case 2:
		//Stay Still, Zero Points
		baseControl(0, 0);
		mogoControl(0, 0);
		tipperControl(0, 0);
		wait1Msec(15000);
		break;

	case 3:
		//Battery Test
		bLCDBacklight = true;
		string mainBattery, backupBattery;

		while(1==1)
		{
			clearLCDLine(0);
			clearLCDLine(1);
			//Primary battery voltage display
			displayLCDString(0, 0, "Primary: ");
			sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
			displayNextLCDString(mainBattery);
			//Backup battery voltage display
			displayLCDString(1, 0, "Backup: ");
			sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');
			displayNextLCDString(backupBattery);
			wait1Msec(100);
		}
		break;

		case 4:
		//Defensive, straight backwards
		baseControl(-127, -127);
		wait1Msec(3000);
		baseControl(0, 0);
		mogoControl(0, 0);
		tipperControl(0, 0);
		break;

	default:
		break;
	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void mogoControlR(int rightMogo, int leftMogo)
{
	motor[leftMobileGoal] = leftMogo;
	motor[rightMobileGoal] = rightMogo;
}
void tipperControlR(int rightTip, int leftTip)
{
	motor[leftTipper] = leftTip;
	motor[rightTipper] = rightTip;
	//nice
}

task usercontrol()
{


	while (true)
	{
		{
			motor[leftSideDrive] = vexRT[Ch3];
			motor[rightSideDrive] = vexRT[Ch2];

			if(vexRT[Btn6U] == 1)
			{
				mogoControlR(-127, -127);
			}
			else if(vexRT[Btn6D] == 1)
			{
				mogoControlR(127, 127);
			}
			else
			{
				mogoControlR(0, 0);
			}
			if(vexRT[Btn5D] == 1)
			{
				tipperControlR(-127, -127);
			}
			else if(vexRT[Btn5U] == 1)
			{
				tipperControlR(127, 127);
			}
			else
			{
				tipperControlR(0, 0);
			}
		}
	}
}
