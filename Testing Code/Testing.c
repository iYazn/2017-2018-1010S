#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           righttower,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           lefttower,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           righttower1,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          claw,          tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	motor[claw] = 127;
	motor[righttower] = 127;
	motor[lefttower] = 127;
	wait1Msec(3000);
	motor[claw] = - 127;
	wait1Msec(3000);


}
