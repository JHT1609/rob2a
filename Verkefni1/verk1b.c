#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop)

//10.16*pi = 31.9186
//50/31.9186 = 1.5665
//1.5665*360 = 563.9348

const int BASEDIST = 564;

void resetEncoder(){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder]  = 0;
}
void drive(int dist, int backw_forw){
	while(abs(SensorValue[leftEncoder]) < dist)
	{
		if(SensorValue[rightEncoder] == SensorValue[leftEncoder])
		{
			motor[rightMotor] = 80*backw_forw;
			motor[leftMotor]  = 80*backw_forw;
		}
		else if(SensorValue[rightEncoder] > SensorValue[leftEncoder])
		{
			motor[rightMotor] = 60*backw_forw;
			motor[leftMotor]  = 80*backw_forw;
		}
		else
		{
			motor[rightMotor] = 80*backw_forw;
			motor[leftMotor]  = 60*backw_forw;
		}
	}
}
task main()
{
	wait1Msec(2000);
	for(int i = 1;i<6;i++){
		resetEncoder();
		drive(BASEDIST*i,1);
		resetEncoder();
		drive(BASEDIST*i,-1);
	}
}
