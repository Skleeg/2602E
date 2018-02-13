motor[rightSideDrive] = 58;
		motor[leftSideDrive] = forwards;
		wait1Msec(2500);
		//drives forwards to mobile goal
		motor[rightSideDrive] = 0;
		motor[leftSideDrive] = 0;
		wait1Msec(500);
		//stops
		motor[gripMotor] = forwards;
		wait1Msec(500);
		//drops preload onto mobile goal
		motor[gripMotor] = nada;
		wait1Msec (100);
		//stops passive intake
		motor[rightMobileGoal] = backwards;
		motor[leftMobileGoal] = -115;
		wait1Msec(750);
		//mobile goal lift picks up mobile goal
		motor[rightSideDrive] = -58;
		motor[leftSideDrive] = backwards;
		wait1Msec(2000);
		//robot goes in reverse
		motor[rightSideDrive] = backwards;
	motor[leftSideDrive] = nada;
	wait1Msec(2100);
	//robot turns and points towards corner
	motor[rightSideDrive] = nada;
	motor[leftSideDrive] = nada;
	wait1Msec(100);
	//robot stops
	motor[rightSideDrive] = 58;
	motor[leftSideDrive] = 105;
	wait1Msec(3000);
	//goes towards zone
	motor[rightSideDrive] = nada;
	motor[leftSideDrive] = nada;
	wait1Msec(100);
	//stops
	motor[leftMobileGoal] = forwards;
		motor[rightMobileGoal] = forwards;
		wait1Msec(1000);
		//drops mobile goal
		motor[leftMobileGoal] = nada;
		motor[rightMobileGoal] = nada;
		wait1Msec(500);
		//stops
		motor[rightSideDrive] = -60;
 motor[leftSideDrive] = -110;
 wait1Msec(1000);
 //backs up
 motor[rightSideDrive] = nada;
 motor[leftSideDrive] = nada;
 wait1Msec(100);
 //stops
task main()
{



}
