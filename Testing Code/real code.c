#pragma config(Motor,  port1,           rightback,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftback,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while (1==1)
	{
		motor(rightback) = vexRT[Ch2];
		motor(leftback) = vexRT[Ch3];
		if (vexRT[Ch2] == 1 )
		{
			motor(rightback) = vexRT[Ch2];
		}
		else if (vexRT(leftback) == 1)
		{
			motor(leftback) = vexRT[Ch3];
		}
		else
		{
			motor(rightback) = motor(leftback) = 0;
		}

	}
}
