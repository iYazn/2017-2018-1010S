#pragma config(Sensor, in1,    Tower,          sensorPotentiometer)
#pragma config(Sensor, dgtl1,  RightBase,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LeftBase,       sensorQuadEncoder)
#pragma config(Motor,  port1,           RightBack,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LeftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LeftLift,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,            ,             tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,            ,             tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LeftBack,      tmotorVex393_HBridge, openLoop)
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
/*===================================================================*\
| Initilize Global Variables..........................................|
|---------------------------------------------------------------------|
| these variables are used in methods that deal with auton all the    |
| way to decalaring variables for battery voltage                     |
\*===================================================================*/
//int statement used for numbers.
int myAutonomous = 50;

/*===================================================================*\
| Meme................................................................|
|---------------------------------------------------------------------|
| used to illustrate the fact that Eric is very sexist and this is    |
| now used to make our user control work                              |
\*===================================================================*/
//Bool statement used for true and false
bool Goalposition = false; //this variable will decide wheather the goal is up or down.
bool held = true; //if the arm needs to be held in position or not.

/*===================================================================*\
| Auton Names.........................................................|
|---------------------------------------------------------------------|
| declares the constant strings for the different auton names that    |
| are then displayed on the LCD display, also contains the open and   |
| close string for the claw method for easier use                     |
\*===================================================================*/
const string autonOne = "Skills";
const string autonTwo = "North Union Red";
const string autonThree = "North Union Blue";
const string autonFour = "High Goal Red -";
const string autonFive = "High Goal Blue -";
const string autonSix = "High Goal Red";
const string autonSeven = "High Goal Blue";
const string autonEight = "Mobile Red";
const string autonNine = "Mobile Blue";
const string autonTen = "Special";
const string autonTest = "Test";
string open = "open";
string close = "close";

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
void SetRight(int power)
{
	motor[RightFront] = motor[LeftFront] = power;
}
void SetLeft(int power)
{
	motor[LeftFront] = motor[LeftBack] = power;
}
void Stop()
{
	motor[LeftFront] = motor[LeftBack] = motor[RightFront] = motor[RightBack] = 0;
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
void SetBase(int power)
{
	motor[LeftFront] = motor[LeftBack] = motor[RightFront] = motor[RightBack] = power;
}
void RightPointTurn(int distance)
{
		while(abs(SensorValue[LeftBase]) < distance)
	{
		SetRight(-127);
		SetLeft(127);
	}
	SetBase(0);
}
void LeftPointTurn(int distance)
{
		while(abs(SensorValue[RightBase])<distance)
	{
		SetRight(127);
		SetLeft(-127);
	}
	SetBase(0);
}
/* void TowerRise(int power, int time)
{
	motor[RTower] = motor[LTower]  = power;
	wait1Msec(time);
}
void TowerDown(int power, int time)
{
	motor[RTower] = motor[LTower]  = -power;
	wait1Msec(time);
}
void TowerStop(int time)
{
	motor[RTower] = motor[LTower] = 0;
	wait1Msec(time);
}
*/
void Move(int power, int distance)
{
	SensorValue[LeftBase] = 0;
	SensorValue[RightBase] = 0;
	float kp = 0.5;//proportional constant, can be tuned.
	while(abs(SensorValue[RightBase]+SensorValue[LeftBase])/2 < distance)
		{
			int error = SensorValue[LeftBase] - SensorValue[RightBase];
			//find the difference between the two encoders.
			SetLeft(power - error*kp);
			SetRight(power + error*kp);
		}//end while
		SetRight(0);
		SetLeft(0);
	}// end MoveForward

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
	/*
	wait1Msec(200);							// Robot waits for 200 milliseconds before executing program
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;////Clear the right and left encoder value
  TowerRise(127, 700);
  TowerStop(10);
  Lift(-127, 1520);
	LiftStop(10);
	Move(127, 922);
	Stop(200);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Lift(127, 1450);
	LiftStop(100);
	Move(-80, 1050);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	RightPointTurn(300);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Stop(100);
	Move(127, 300);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Stop(100);
	RightPointTurn(300);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Stop(100);
	Move(127, 400);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Stop(100);
	Lift(-127, 900);
	LiftStop(100);
	Move(127, 120);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Lift(-127, 200);
	Move(-127, 600);
	SensorValue[RightBase] = SensorValue[LeftBase] = 0;
	Stop(100);
	*/

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
	  motor[RightFront] = motor[RightBack] = vexRT(Ch2) - vexRT(Ch1);//combine Right Motors all forward.
		motor[LeftBack] = motor[LeftFront] = vexRT(Ch2) + vexRT(Ch1);//combine Left Motors all forward.
		motor[RightFront] = motor[RightBack] = vexRT(Ch2);//combine Right motors all forward.	`````````
		motor[LeftBack] = motor[LeftFront] = vexRT(Ch3)
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

/*		if(vexRT[Btn5U] ==1)
		{
			motor[RTower] = motor[LTower] = 127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[RTower] = motor[LTower] = -127;
		}
		else
		{
			motor[RTower] = motor[LTower] = 0;
		}
*/
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
