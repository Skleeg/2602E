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

void rawBaseControl(int leftSide, int rightSide)
{
	motor[leftSideDrive] = leftSide;
	motor[rightSideDrive] = rightSide:
}

void rawliftControl(int leftSideMogo, int rightSideMogo)
{
	motor[leftMobileGoal] = leftSideMogo;
	motor[rightMobileGoal] = rightSideMogo;
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
void BaseControlPID (float target, float waitTime, float maxPower = 1)
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
			error = inchToTicks(target/2) - (2*(SensorValue(LeftEncoder)));

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

	task GyroReset()
	{
		//Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[in4] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[in4] = sensorGyro;
 wait1Msec(2000);
}

	task PivotLeft90()
{

stopTask(GyroReset);

//Adjust SensorScale to correct the scaling for your gyro
SensorScale[in4] = 51.93;
 //Adjust SensorFullCount to set the "rollover" point. 3600 sets the rollover point to +/-3600
SensorFullCount[in4] = 3600;

//Specify the number of degrees for the robot to turn (1 degree = 10, or 900 = 90 degrees)
 int degrees90 = 900;

//While the absolute value of the gyro is less than the desired rotation...
 while(abs(SensorValue[in4]) < degrees90)
 {
 //...continue turning
 motor[rightSideDrive] = 100;
 motor[leftSideDrive] = -100;
 }

//Brief brake to stop some drift
 motor[rightSideDrive] = -50;
 motor[leftSideDrive] = 50;
 wait1Msec(250);

 rawBaseControl(0, 0);
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
			startTask(GyroReset);
			wait1Msec(2000);

		  startTask(PivotLeft90);
		  //pivot to the left

		  baseControl(0, 0, 250);
		  stopTask(PivotLeft90);
		  rawBaseControl(0, 0);
		  wait1Msec(250);
		  //stop, reset gyro

			BaseControlPID(7.5, 0, 0.5);
			rawBaseControl(0, 0);
			wait1Msec(100);



			//drive forwards to prepare for 20pt
		}
	}


}
