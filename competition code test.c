#pragma config(Motor,  port1,           LeftBack,      tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           LeftFront,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           RightFront,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           RightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LeftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LTowerU,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RTowerU,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LTowerD,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RTowerD,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          RightBack,     tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
void SetRight(int power, int time)
{
	motor[RightFront] = motor[LeftFront] = power;
	wait1Msec(time);
}
void SetLeft(int power, int time)
{
	motor[LeftFront] = motor[LeftBack] = power;
}
void Stop(int time)
{
	motor[LeftFront] = motor[LeftBack] = motor[RightFront] = motor[RightBack] = 0;
	wait1Msec(time);
}
void Lift(int power, int time)
{
	motor[RightLift] = motor[LeftLift] = power;
	wait1Msec(time);
}
void LiftStop(int time)
{
	motor[RightLift] = motor[LeftLift] = 0;
	wait1Msec(time);
}
void SetBase(int power, int time)
{
	motor[LeftFront] = motor[LeftBack] = motor[RightFront] = motor[RightBack] = power;
	wait1Msec(time);
}
void RightPointTurn(int time)
{
	motor[LeftFront] = motor[LeftBack] = 127;
	motor[RightFront] = motor[RightBack] = -127;
	wait1Msec(time);
}
void LeftPointTurn(int time)
{
	motor[LeftFront] = motor[LeftBack] = -127;
	motor[RightFront] = motor[RightBack] = 127;
	wait1Msec(time);
}
void TowerRise(int power, int time)
{
	motor[RTowerU] = motor[LTowerU]  = power;
	motor[RTowerD] = motor[LTowerD] = -power;
	wait1Msec(time);
}
void TowerStop(int time)
{
	motor[RTowerU] = motor[LTowerU] = motor[RTowerD] = motor[LTowerD] = 0;
	wait1Msec(time);
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
	TowerRise(127, 800);
	TowerStop(10);
	Lift(127, 1500);
	LiftStop(100);
	SetBase(127, 1480);
	Stop(100);
	Lift(-127, 1450);
	LiftStop(100);
	SetBase(-80, 2000);
	Stop(30);
	RightPointTurn(775);
	Stop(20);
	SetBase(127, 800);
	Stop(10);
	RightPointTurn(120);
	SetBase(127, 500);
	Stop(100);
	Lift(127, 850);
	LiftStop(100);
	SetBase(127, 220);
	Stop(100);
	SetBase(-127, 700);
	Stop(100);
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
	// User control code here, inside the loop
	while (true)
	{
		motor[RightFront] = motor[RightBack] = vexRT(Ch2);//combine Right motors all forward.	`````````
		motor[LeftBack] = motor[LeftFront] = vexRT(Ch3);//combine Left Motors all forward.
		if(vexRT[Btn6U] == 1)
		{
			motor[RightLift] = motor[LeftLift] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[RightLift] = motor[LeftLift] = -127;
		}
		else
		{
			motor[RightLift] = motor[LeftLift] = 0;
		}

		if(vexRT[Btn5U] ==1)
		{
			motor[RTowerU] = motor[LTowerU] = 127;
			motor[RTowerD] = motor[LTowerD] = -127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[RTowerU] = motor[LTowerU] = -127;
			motor[RTowerD] = motor[LTowerD] = 127;
		}
		else
		{
			motor[RTowerU] = motor[LTowerU] = 0;
			motor[RTowerD] = motor[LTowerD] = 0;
		}
		if(vexRT[Btn8R] == 1)
		{
			motor[LeftFront] = motor[LeftBack] = 127;
			motor[RightFront] = motor[RightBack] = -127;
		}
		else if(vexRT[Btn8L] == 1)
		{
			motor[LeftFront] = motor[LeftBack] = -127;
			motor[RightFront] = motor[RightBack] = 127;
		}
		else
		{
			motor[LeftFront] = motor[LeftBack] = 0;
			motor[RightFront] = motor[RightBack] = 0;
		}

		// This is the main execution loop for the user control program.
		// Each time through the loop your program should update motor + servo
		// values based on feedback from the joysticks.

		// ........................................................................
		// Insert user code here. This is where you use the joystick values to
		// update your motors, etc.
		// ........................................................................

		// Remove this function call once you have "real" code.
		UserControlCodePlaceholderForTesting();
	}
}
