#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop)

int power = 127;
const int BASETIME = 1111;

void drive(int increment, int back_forw){
	motor[rightMotor] = power*back_forw;
	motor[leftMotor] = power*back_forw;
	wait1Msec(BASETIME*increment);
}

task main()
{
	for(int i = 1;i<6;i++){
		drive(i,1);
		drive(i,-1);
	}
}
