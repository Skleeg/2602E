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
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
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

task usercontrol()
{
	int forwards;
	int backwards;
	int nada;

	forwards = 95;
	backwards = -95;
	nada = 0;

	clearTimer(T1);
	while(time1[T1] < 15000)
  {
  	motor[rightSideDrive] = forwards;
		motor[leftSideDrive] = forwards;
		wait1Msec(3000);
		//drives forwards
		motor[rightSideDrive] = nada;
		motor[leftSideDrive] = nada;
		wait1Msec(0);
		//stops
		motor[rightMobileGoal] = backwards;
		m
		wait1Msec(500);
		//mobile goal goes out
		motor[rightSideDrive] = forwards;
		motor[leftSideDrive] = forwards;
		wait1Msec(200);
		//drive forwards to snag mobile goal
		motor[gripMotor] = backwards;
		wait1Msec(300);
		//release cone
		motor[rightMobileGoal] = forwards;
		wait1Msec(500);
		//load mobile goal
		motor[rightSideDrive] = forwards;
		motor[leftSideDrive] = backwards;
		wait1Msec(1000);
		//reverse direction
		motor[rightSideDrive] = forwards;
		motor[leftSideDrive] = forwards;
		wait1Msec(2500);
		//drive back to scoring pipes
		//might need to change time for wait variable
		motor[rightMobileGoal] = backwards;
		wait1Msec(500);
		//release mobile goal
		motor[rightSideDrive] = backwards;
		motor[leftSideDrive] = backwards;
		wait1Msec(1000);
		//drive out of scoring pipes
		motor[rightSideDrive] = backwards;
		motor[leftSideDrive] = forwards;
		wait1Msec(1000);
		//turn to the right
		motor[rightSideDrive] = forwards;
		motor[leftSideDrive] = forwards;
		wait1Msec(1000);
		//drive forwards
		motor[rightSideDrive] = nada;
		motor[leftSideDrive] = nada;
		wait1Msec(0);
		//stop


  }
}
