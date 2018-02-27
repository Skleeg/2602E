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


void rawliftControl (int leftLift, int rightLift)
{
	motor[leftMobileGoal] = leftLift;
	motor[rightMobileGoal] = rightLift;
}

void PIDliftControl (int LiftSpeed)
{
		motor[leftMobileGoal] = LiftSpeed;
		motor[rightMobileGoal] = LiftSpeed;
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
void LiftControlPID (float target, float waitTime, float maxPower=1)
{
	float Kp = 0.3;
	float Ki = 0;
	float Kd = 1.2;


	int error;

	float proportion;
	int integralRaw;
	float integral;
	int lastError;
	int derivitave;


	int finalPower;

	bool timerBool = true;



	clearTimer(T1);

	while(time1[T1] < fixTimerValue(waitTime))
	{
		error = (target/2) - (2*(SensorValue(RightPotentiometer)));

		proportion = Kp*error;
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

		PIDliftControl((finalPower)*-1);

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
	PIDliftControl(0);
}

task main()
{
	rawliftControl(63, 63); untilPotentiometerGreaterThan(1200, in3);
	rawliftControl(0, 0,);
	wait1Msec(1000);
	LiftControlPID(1200, 0, 0.5);

}
