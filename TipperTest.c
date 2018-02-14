#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightTipper,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftTipper,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,            ,             tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
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
	}
	{
		motor[leftSideDrive] = vexRT[Ch3];
		motor[rightSideDrive] = vexRT[Ch2];

		if(vexRT[Btn6U] == 1)
		{
			motor[rightMobileGoal] = -127;
			motor[leftMobileGoal] = -127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[rightMobileGoal] = 127;
			motor[leftMobileGoal] = 127;
		}
		else
		{
			motor[rightMobileGoal] = 0;
			motor[leftMobileGoal] = 0;
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

}
}
