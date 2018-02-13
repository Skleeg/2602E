#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in5,    LeftLine,       sensorLineFollower)
#pragma config(Sensor, in6,    CenterLine,     sensorLineFollower)
#pragma config(Sensor, in7,    RightLine,      sensorLineFollower)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mainLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           turntableMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           gripMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftExtension, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)\\

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("Motors")

void moveBase (int speed)
{
		motor[leftSideDrive] = speed;
		motor[rightSideDrive] = speed;
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
void PIDBaseControl (float target, float waitTime)
{
		float Kp = 0.2;
		float Ki = 0.05;

		int error;

		float proportion;
		int integralRaw;
		float integral;

		float integralActiveZone = inchToTicks(3);
		float integralPowerLimit = 50/Ki;

		int finalPower;

		bool timerBool = true;

		SensorValue(LeftEncoder) = 0;
		SensorValue(RightEncoder) = 0;


		clearTimer(T1);

		while(time1[T1] < fixTimerValue(waitTime))
		{
			error = inchToTicks(target) - (SensorValue[RightEncoder]) +(SensorValue[LeftEncoder]);

			proportion = Kp*error;

			if (abs(error) < integralActiveZone && error != 0)
			{
				integralRaw = integralRaw+error;
			}
			else
			{
				integralRaw = 0;
			}

			if (integralRaw > integralPowerLimit)
			{
				integralRaw = integralPowerLimit;
			}
			if (integralRaw < - integralPowerLimit)
			{
				integralRaw = -integralPowerLimit;
			}

			integral = Ki*integralRaw;

			finalPower = proportion+integral; //proportion+derivitave + intergral

			moveBase(finalPower);

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
	moveBase(0);
}

task main()
{
	PIDBaseControl(12, 0.25); //move forward 12 inches with 1 sec delay;
	PIDBaseControl(-7.5, 1); //back off 7.5 inches with 1 sec delay;

	while(true)
			{
			wait1Msec(20);
			}
}
