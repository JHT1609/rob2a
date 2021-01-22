#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop)

// 10.16*pi = 31.9186
// 50/31.9186 = 1.5665
// 1.5665*360 = 563.9348
const int BASEDIST = 564;

int power = 127;

// 28*pi=87.96
// 87.96/31.92=2.76
const int BASEDEG = 2.8;

void turn(int deg, int leftRight){
	while(SensorValue[leftEncoder]<deg*BASEDEG && SensorValue[leftEncoder]>-(deg*BASEDEG)){
	motor[leftMotor] = -power*leftRight;
	motor[rightMotor] = power*leftRight;
}
}
void drive(int dist){
	while(abs(SensorValue[leftEncoder]) < dist){
		motor[rightMotor] = 80;
		motor[leftMotor]  = 80;
	}
}
void stopMotors(){
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}
void resetEncoder(){
	SensorValue[leftEncoder]=0;
	SensorValue[rightEncoder]=0;
}
int path[14]={1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,1};
task main()
{
	for(int i =0;i<14;i++) {
		resetEncoder();
		drive(BASEDIST);
		stopMotors();
		resetEncoder();
		turn(90,path[i]);
		stopMotors();
		}
}
