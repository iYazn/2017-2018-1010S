#pragma config(Sensor, in1,    RTower,         sensorPotentiometer)
#pragma config(Sensor, in2,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  REncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  LCD1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl6,  LCD2,           sensorLEDtoVCC)
#pragma config(Motor,  port1,           RClaw,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RFront,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LFront,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RLift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LLift,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           RBack,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LBack,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LTower,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RTower,        tmotorVex393_MC29, openLoop, reversed)
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

int myauto = 1;


const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 5;

void autoselector(){
		clearLCDLine(0);
    clearLCDLine(1);
    bLCDBacklight = true;
		while(bIfiRobotDisabled){
			switch(myauto){
				case(1):
					displayLCDCenteredString(0, "Right 20");
					displayLCDCenteredString(1, "1010S");
						if(nLCDButtons == leftButton){
							while(nLCDButtons != 0){}
							wait1Msec(5);
							myauto = 1;
							}
						else if(nLCDButtons == rightButton){
							while(nLCDButtons != 0){}
							wait1Msec(5);
							myauto = 2;
						}
						else{}
				break;
				case(2):
					displayLCDCenteredString(0, "Left 20");
					displayLCDCenteredString(1, "1010S");
					if(nLCDButtons == leftButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 1;
						}
					else if(nLCDButtons == rightButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 3;
						}
					else{}
				break;
				case(3):
					displayLCDCenteredString(0, "Right 10");
					displayLCDCenteredString(1, "1010S");
					if(nLCDButtons == leftButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 2;
						}
					else if(nLCDButtons == rightButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 4;
						}
					else{}
				break;
				case(4):
					displayLCDCenteredString(0, "Left 10");
					displayLCDCenteredString(1, "1010S");
					if(nLCDButtons == leftButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 3;
						}
					else if(nLCDButtons == rightButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 5;
						}
					else{}
				break;
				case(5):
					displayLCDCenteredString(0, "Skill");
					displayLCDCenteredString(1, "1010S");
					if(nLCDButtons == leftButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 4;
						}
					else if(nLCDButtons == rightButton){
						while(nLCDButtons != 0){}
						wait1Msec(5);
						myauto = 5;
						}
					else{}
				break;
				break;
				default:
					myauto = 1;
				break;
				}
			}
}

void pre_auton()

{
	bStopTasksBetweenModes = true;
	bDisplayCompetitionStatusOnLcd = false;
	SensorType[Gyro] = sensorNone;
	SensorType[LEncoder] = sensorNone;
	SensorType[REncoder] = sensorNone;
	// waits 1 sec before setting all the sensors
	wait1Msec(1000);
	SensorType[Gyro] = sensorGyro;
	SensorType[LEncoder] = sensorQuadEncoder;
	SensorType[REncoder] = sensorQuadEncoder;
	// waits 2 seconds to let gyro initilize properly
	// DO NOT MOVE WHILE THIS IS HAPPENING
	wait1Msec(2000);
	autoselector();
}

//set sensors to zero.
void setDrive ()
{
	// resets encoder values to 0
	SensorValue(LEncoder) = 0;
	SensorValue(REncoder) = 0;
}

void setGyro ()
{
	// resets the gyro value to 0
	SensorValue(Gyro) = 0;
}

//combine motors together
void SetRight(int power)
{
	motor[RFront] = motor[RBack] = power;
}

void SetLeft(int power)
{
	motor[LFront] = motor[LBack] = power;
}

void StopDrive()
{
	motor[RFront] = motor[LFront] = motor[RBack] = motor[LBack] = 0;
}

void StopLift()
{
	motor[RLift] = motor[LLift] = 0;
}

void StopTower()
{
	motor[RTower] = motor[LTower] = 0;
}

void StopClaw(int power, int time)
{
	motor[RClaw] = motor[LClaw] = 0;
}

void Move(int power, int distance)
{
	SensorValue[LEncoder] = 0;
	SensorValue[REncoder] = 0;
	float kp = 0.5;//proportional constant, can be tuned.
	while(abs(SensorValue[REncoder]+SensorValue[LEncoder])/2 < distance)
		{
			int error = SensorValue[LEncoder] - SensorValue[REncoder];
			//find the difference between the two encoders.
			SetLeft(power - error*kp);
			SetRight(power + error*kp);
		}//end while
		setDrive();
	}// end MoveForward

void gyroturnL(int power, int gyrovalue){

	SensorValue[Gyro] = 0;

	while (SensorValue[Gyro] >= gyrovalue)
{

		motor[RFront] = motor[RBack] = -power;

		motor[LFront] = motor[LBack] = power;

	}

	motor[RFront] = motor[RBack] = motor[LFront] = motor[LBack] = 0;

	wait1Msec(10);
}

void gyroturnR(int power, int gyrovalue){
	SensorValue[Gyro] = 0;

	while (SensorValue[Gyro] >= gyrovalue)
{

		motor[RFront] = motor[RBack] = power;

		motor[LFront] = motor[LBack] = -power;

	}

	motor[RFront] = motor[RBack] = motor[LFront] = motor[LBack] = 0;

	wait1Msec(10);
}

void RightPointTurn(int distance)
{
		while(abs(SensorValue[LEncoder]) < distance)
	{
		SetRight(-127);
		SetLeft(127);
	}
	SetDrive();
}
void LeftPointTurn(int distance)
{
		while(abs(SensorValue[REncoder])<distance)
	{
		SetRight(127);
		SetLeft(-127);
	}
	SetDrive();
}

void TowerRise(int position)
{
	while(SensorValue[RTower] < position;
	{
	motor[RTower] = motor[LTower]  = 127;
	}

	motor[RTower] = motor[LTower] = 0;
}

void TowerDown(int position)
{
	while(SensorValue[RTower] > position)
	{
	motor[RTower] = motor[LTower]  = -127;
	}

	motor[RTower] = motor[LTower] = 0;
}

void Lift(int power, int time)
{
	motor[RLift] = motor[LLift] = power;
	wait1Msec(time);
}

void Claw(int power, int time)
{
	motor[RClaw] = motor[LClaw] = power;
	wait1Msec(time);
}

void driveBase(){
		motor[RFront] = motor[RBack] = vexRT(Ch2) - vexRT(Ch1);//combine Right Motors all forward.
		motor[LBack] = motor[LFront] = vexRT(Ch2) + vexRT(Ch1);//combine Left Motors all forward.
	}

void driveTower(){
			if(vexRT[Btn5U] ==1)
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
	}

void driveLift(){
			if(vexRT[Btn6U] == 1)
		{
			motor[RLift] = motor[LLift] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[RLift] = motor[LLift] = -127;
		}
		else
		{
			motor[RLift] = motor[LLift] = 0;
		}
	}

void driveClaw(){
	motor[LClaw] = motor[RClaw] = vexRT(Ch3);
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

int TowerHold = 1; //Tower loop flag
int TowerPosition = 0; // Position to set the tower

task TowerTask()
{
	TowerPosition = SensorValue[RTower];
	while(true)
	{
		if(TowerHold)//should tower code be running?
		{
			//calculate difference
		int difference = (SensorValue[RTower] - TowerPosition)*0.5;

		//Cap difference value if needed
		if(difference > 127)
			difference = 127;
		else if(difference < -127)
			difference = -127;

			motor[RTower] = motor[LTower] = difference;
		}
	}
}

task autonomous()
{
	clearLCDLine(0);

  clearLCDLine(1);

  bLCDBacklight = true;

  displayLCDCenteredString(0, "Let's Go!");

  switch(myauto){

		case 1:

		break;



		case 2:

		break;



		case 3:

		break;



		case 4:

		break;

		case 5:

		break;
	}
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
