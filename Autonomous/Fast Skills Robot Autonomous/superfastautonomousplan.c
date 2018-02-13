#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightSideDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMobileGoal, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mainLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           turntableMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftSideDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           gripMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftExtension, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftMobileGoal, tmotorVex393_MC29, openLoop)

void baseControl(int leftPower, int rightPower)
{
	motor[leftSideDrive] = leftPower;
	motor[rightSideDrive] = rightPower;
}

task main()
{

int forwards;
int backwards;
int nada;

forwards = 127;
backwards = -127;
nada = 0;

//motor[rightSideDrive] = forwards;
//motor[leftSideDrive] = forwards;
//baseControl(forwards,forwards);

wait1Msec(1000);
//Drive from the start, straight forward to the B1 cone
motor[rightSideDrive] = nada;
motor[leftMobileGoal] = nada;
wait1Msec(100);
//stop
motor[rightSideDrive] = backwards;
motor[leftSideDrive] = backwards;
wait1Msec(1000);
//Drive back to start
motor[rightSideDrive] = nada;
motor[leftSideDrive] = nada;
wait1Msec(100);
//stop
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = backwards;
wait1Msec(100);
//turn and face corner directly
motor[rightSideDrive] = nada;
motor[leftSideDrive] = nada;
wait1Msec(100);
//stop
motor[rightSideDrive] = backwards;
motor[leftSideDrive] = -60;
wait1Msec(400);
//turn towards cone B4
motor[rightSideDrive] = nada;
motor[leftSideDrive] = nada;
wait1Msec(100);
//stop
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = forwards;
wait1Msec(1000);
//drive forwards to B4
motor[rightSideDrive] = nada;
motor[leftSideDrive] = nada;
wait1Msec(100);
//stop
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = backwards;
wait1Msec(500);
//reverses and faces towards corner
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = forwards;
wait1Msec(750);
//goes to 10 pt zone
//insert dropping of mobile goal
//insert mobile goal lift going back in
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = backwards;
wait1Msec(250);
//faces towards R3
//insert mobile goal lift going down
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = forwards;
wait1Msec(750);
//drive towards R3
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = backwards;
wait1Msec(500);
//face towards 10 pt zone
motor[rightSideDrive] = nada;
motor[leftSideDrive] = nada;
wait1Msec(100);
//stop
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = forwards;
wait1Msec(750);
//drive to 10 pt zone
//drop mobile goal
motor[rightSideDrive] = backwards;
motor[leftSideDrive] = backwards;
//insert mobile goal going back in too
wait1Msec(1500);
//stops in front of cone B3
motor[rightSideDrive] = nada;
motor[leftSideDrive] = nada;
wait1Msec(200);
//stops in front of B3
motor[rightSideDrive] = forwards;
motor[leftSideDrive] = backwards;
wait1Msec(250);
//point towards B3
motor[rightSideDrive] = 117;
motor[leftSideDrive] = forwards;
wait1Msec(1500);
//drive to 20 pt zone
//stop before
//drop mobile goal
baseControl(forwards, backwards);
wait1Msec(250);
//turn around and face R4
baseControl(forwards, forwards;
wait1Msec(750);
//drive to r4
//drop down mobile goal lift
}
