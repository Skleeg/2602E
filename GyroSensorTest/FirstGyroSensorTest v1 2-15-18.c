#pragma config(Sensor, in1,    LeftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    RightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in4,    GyroSensor,     sensorGyro)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightTipper,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftTipper,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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

task main()
{
//Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[in4] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[in4] = sensorGyro;
 wait1Msec(2000);

//Adjust SensorScale to correct the scaling for your gyro
SensorScale[in4] = 260;
 //Adjust SensorFullCount to set the "rollover" point. 3600 sets the rollover point to +/-3600
SensorFullCount[in8] = 3600;

//Specify the number of degrees for the robot to turn (1 degree = 10, or 900 = 90 degrees)
 int degrees10 = 20;

//While the absolute value of the gyro is less than the desired rotation...
 while(abs(SensorValue[in8]) < degrees10)
 {
 //...continue turning
 motor[rightSideDrive] = 25;
 motor[leftSideDrive] = -25;
 }

//Brief brake to stop some drift
 motor[rightSideDrive] = -5;
 motor[leftSideDrive] = 5;
 wait1Msec(250);



}
