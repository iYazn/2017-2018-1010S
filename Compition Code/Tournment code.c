#pragma config(Sensor, in1,    RTower,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  REncouder,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LEncouder,      sensorQuadEncoder)
#pragma config(Motor,  port1,           RClaw,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           RFront,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LFront,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RLift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LLift,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           Rback,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           Lback,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LTower,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RTower,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LClaw,         tmotorVex393_HBridge, openLoop)
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

void SetRight(int power){
	motor[RFront] = motor[RBack] = power;
}

void SetLeft(int power)(
	motor[LFront] = motor[LBack] = power;
}

/*===================================================================*\
| Resets Drive Encoder................................................|
|---------------------------------------------------------------------|
| sets the drive encoders to 0 to then be used throughout the methods |
\*===================================================================*/
void setDrive (){
	// resets encoder values to 0
	SensorValue(REncouder) = 0;
	SensorValue(LEncouder) = 0;
}

/*===================================================================*\
| Stop Drive..........................................................|
|---------------------------------------------------------------------|
| completly stops the drive motors, used in auton methods             |
\*===================================================================*/
void StopDrive()
{
	motor[RFront] = motor[LFront] = motor[RBack] = motor[LBack] = 0
}

/*===================================================================*\
| Stop Mobile Goal....................................................|
|---------------------------------------------------------------------|
| completly stops the mobile goal lift motors                         |
\*===================================================================*/
void StopLift()
{
	motor[RLift] = motor[LLift] = 0;
}

/*------------------------------------------------------------------*\
//	______      _
//	|  _  \    (_)
//	| | | |_ __ ___   _____
//	| | | | '__| \ \ / / _ \
//	| |/ /| |  | |\ V /  __/
//	|___/ |_|  |_| \_/ \___|
\*------------------------------------------------------------------*/

/*===================================================================*\
| Move..........................................................|
|---------------------------------------------------------------------|
| allows the use for timing when controling the drive, but also uses  |
| the drive straight commands                                         |
\*===================================================================*/
void Move(int power, int distance)
{
	SetDrive();
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

void RightPointTurn(int distance)
{
		while(abs(SensorValue[LeftBase]) < distance)
	{
		SetRight(-127);
		SetLeft(127);
	}
	SetDrive(0);
}
void LeftPointTurn(int distance)
{
		while(abs(SensorValue[RightBase])<distance)
	{
		SetRight(127);
		SetLeft(-127);
	}
	SetDrive(0);
}

void Move(int power, int distance)
{
	SensorValue[LeftBase] = 0;
	SensorValue[RightBase] = 0;
	float kp = 0.2;//proportional constant, can be tuned.
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

void TowerRise(int power, int time)
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

void Lift(int power, int time)
{
	motor[RLift] = motor[LLift] = power;
	wait1Msec(time);
}

void LiftStop(int time)
{
	motor[RLift] = motor{LLift] = 0;
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
