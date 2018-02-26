#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in2,    CenterLine,     sensorLineFollower)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in4,    GyroSensor,     sensorGyro)
#pragma config(Sensor, in6,    LeftLine,       sensorLineFollower)
#pragma config(Sensor, in7,    RightLine,      sensorLineFollower)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightTipper,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftTipper,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)

task Battery()
{
bLCDBacklight = true;
string mainBattery, backupBattery;

while(true)
{
	clearLCDLine(0);
	clearLCDLine(1);

	//display

	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	displayLCDString(1, 0, "Backup:  ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0,'V');
	displayNextLCDString(backupBattery);

	wait1Msec(100);
	}
}

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

void tipControl (int leftTip, int rightTip)
{
	motor[rightTipper] = rightTip;
	motor[leftTipper]= leftTip;
}


	task Straighten()
{

int difference;
int leftStart;
int rightStart;


leftStart = 100;
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

task main()
{
	while(1==1)
	{
		if(vexRT(Btn8U) == 1)
		{
			startTask(Battery);
			wait1Msec(100);
		}

		if(vexRT[Btn5U] == 1)
		{
			motor[rightTipper] = -63;
			motor[leftTipper] = -63;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[rightTipper] = 63;
			motor[leftTipper] = 63;
		}
		else
		{
			motor[rightTipper] = 0;
			motor[leftTipper] = 0;
		}

		if(vexRT(Btn8R) == 1)
		{
			tipControl(100, 100);
			wait1Msec(500);
			//move tip out of the way

			startTask(Straighten);

		}
	}


}
