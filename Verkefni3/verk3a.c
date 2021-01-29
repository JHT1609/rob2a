#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl1,  sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in2,    lightSensor,         sensorReflection)
#pragma config(Sensor, dgtl9,  stopButton,     sensorTouch)
#pragma config(Motor,  port1,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorServoContinuousRotation, openLoop)

int power = 127;

task stopMyTask(){
	while(SensorValue[stopButton] == 0 && vexRT[Btn7L]==0){ //medan ekki er itt a takka gerist ekki, annars keirir stopalltasks
		}
		StopAllTasks();
}

void resetEncoder(){
	SensorValue[leftEncoder]=0;
	SensorValue[rightEncoder]=0;
}

void drive(int dist){
	while(abs(SensorValue[leftEncoder]) < dist){
		motor[rightMotor] = power;
		motor[leftMotor]  = power;
	}
}

void turn(){
	while(abs(SensorValue[leftEncoder])<90*2.8){
	motor[leftMotor] = -power;
	motor[rightMotor] = power;
	}
}

task main()
{
	StartTask(stopMyTask);

	while(true){
	while(SensorValue(sonarSensor) <= 50){	//beygja medan bil er minna en 50 tommur
	turn();
	}
	while(SensorValue(lightSensor) < 500 && SensorValue(sonarSensor) > 50) //medan ljos og bil eru i lagi
	{
		resetEncoder();
		drive(50);	//keyrir loopu fyrir hver 50 stig a encoder
	}
	motor[rightMotor] = 0; // reset encoder
	motor[leftMotor]  = 0;
}

}
