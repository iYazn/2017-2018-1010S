
//gyroTurn(right,900)
//gyroTurn( left,-900)
#define LEFT 1
#define RIGHT -1

void gyroTurn (int direction,int target) { //for autonomous when it turn it turn really acurately and we change kp values to reduce error
	//target is the angle that we wanted
	int error = target; //target is what we get the number ) //we decide the angle in switch case break? in autonomous some where else
	float errorSum = 0; //error sum is to make it more accurate like turn back left or right a lot more accurate
	int output;
	float kp = 0.2;// make it slower? if constant less  //whats the difference between float and int? errorsum?why float?
	float ki = 0.00010;
	target *= direction;
	target += Sensorvalue[gyro];   //for gyro when turn clockwise value will be negative counter clockwise value positive
	//+=????
	while (error > 0) {
		//-900              0->-900   //negative turn right
		error = target - Sensorvalue[gyro];
		if (error < 100)
			errorSum = errorSum + error;
		//down here output will also be negative
		output = error * kp + errorSum * ki;

		leftdrive = -output; //if want to turn right the output is negative at first so when (-(-output)) its gonna be positive which mean turn right
		right drive = +output;
	}

	leftdrive = right drive = 0;
}}
