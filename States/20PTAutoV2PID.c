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

void PIDbaseControl (int speed)
{
		motor[leftSideDrive] = speed;
		motor[rightSideDrive] = speed;
}

void straightBaseControl (int leftSide, int rightSide)
{
	leftSide = motor[leftSideDrive];
	rightSide = motor[rightSideDrive];
}

void baseControl(int leftPower, int rightPower, int baseTime)
{
	motor[leftSideDrive] = leftPower;
	motor[rightSideDrive] = rightPower;
	baseTime = wait1Msec(baseTime);
}

void liftControl (int leftLift, int rightLift, int liftTime)
{
	motor[leftMobileGoal] = leftLift;
	motor[rightMobileGoal] = rightLift;
	liftTime = wait1Msec(liftTime);
}

void tipControl (int leftTip, int rightTip, int tipTime)
{
	motor[rightTipper] = rightTip;
	motor[leftTipper]= leftTip;
	tipTime = wait1Msec(tipTime);
}

//reading: ticks -- 627.2ticks/revolution
// 1 turn of the wheels -- 4 inch wheels = 627.2 *2 ticks
//1 turn of each wheel 4*pi inches
//4*pi inches = 627.2*2 ticks

//ticks/inch = 627.2 * 2 /4*pi= 99.82198


int inchToTicks (float inch)
{
		int ticks;
		ticks = inch*99.82198;
		return ticks;
 }

int fixTimerValue (float rawSeconds)
{
	int miliseconds;
	miliseconds = rawSeconds*1000;
	if (miliseconds < 250)
	{
			miliseconds = 250;
	}
	return miliseconds;
}
void PIDBaseControl (float target, float waitTime, float maxPower = 1)
{
		float Kp = 0.26;
		float Ki = 0.05;
		float Kd = 0.62;

		int RightSensor;
		int LeftSensor;

		RightSensor = SensorValue[RightEncoder]*-1;
		LeftSensor = SensorValue[LeftEncoder];

		int error;

		float proportion;
		int integralRaw;
		float integral;
		int lastError;
		int derivitave;

		float integralActiveZone = inchToTicks(3);


		int finalPower;

		bool timerBool = true;

		SensorValue(LeftEncoder) = 0;
		SensorValue(RightEncoder) = 0;


		clearTimer(T1);

		while(time1[T1] < fixTimerValue(waitTime))
		{
			error = inchToTicks(target/2) - (2*(SensorValue(LeftEncoder));

			proportion = Kp*error;

			if (abs(error) < integralActiveZone && error != 0)
			{
				integralRaw = integralRaw+error;
			}
			else
			{
				integralRaw = 0;
			}

			integral = Ki*integralRaw;

			derivitave = Kd*(error-lastError);
		 	lastError = error;

		 	if (error == 0)
		 	{
		 			derivitave = 0;
			}

			finalPower = proportion+integral+derivitave; //proportion+derivitave + intergral

			if(finalPower > maxPower*127)
			{
				finalPower = maxPower*127;
			}
			else if(finalPower < -maxPower*127)
			{
				finalPower= -maxPower*127;
			}

			PIDbaseControl(finalPower);

			wait1Msec(40);

			if (error < 30)
			{
					timerBool = false;
			}

			if (timerBool)
			{
				clearTimer(T1);
			}
	}
	PIDbaseControl(0);
}


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
			straightBaseControl(leftStart, rightStart);
		}

		if(SensorValue(RightEncoder) > SensorValue(LeftEncoder))
		{
			straightBaseControl(leftStart, (rightStart - difference));
		}

		if(SensorValue(LeftEncoder) > SensorValue(RightEncoder))
		{
			straightBaseControl((leftStart - difference), rightStart);
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
			straightBaseControl(leftStart, rightStart);
		}

		if(SensorValue(RightEncoder) > SensorValue(LeftEncoder))
		{
			straightBaseControl(leftStart, (rightStart - difference));
		}

		if(SensorValue(LeftEncoder) > SensorValue(RightEncoder))
		{
			straightBaseControl((leftStart - difference), rightStart);
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
			straightBaseControl(leftStart, rightStart);
		}

		if(SensorValue(RightEncoder) > SensorValue(LeftEncoder))
		{
			straightBaseControl(leftStart, (rightStart - difference));
		}

		if(SensorValue(LeftEncoder) > SensorValue(RightEncoder))
		{
			straightBaseControl((leftStart - difference), rightStart);
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
			tipControl(100, 100, 150);
			//move tip out of the way

			liftControl(127, 127, 175);
			//bring mobile goal down

			startTask(Straighten);
			straightBaseControl(127, 127);
			wait1Msec(500);
			stopTask(Straighten);
			//drive to red mobile goal


		}
	}


}
