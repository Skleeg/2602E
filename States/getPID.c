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

			PIDBaseControl(finalPower);

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
	PIDBaseControl(0);
}
