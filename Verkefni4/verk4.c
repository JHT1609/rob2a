#pragma config(Sensor, in5,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl1,  sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, dgtl9,  stopButton,     sensorTouch)
#pragma config(Motor,  port1,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorServoContinuousRotation, openLoop)

void turn(){
	while(abs(SensorValue[leftEncoder])<90*2.8){
	motor[leftMotor] = -127;
	motor[rightMotor] = 127;
	}
}

task stopMyTask(){
	while(SensorValue[stopButton] == 0 && vexRT[Btn7L]==0){
		}
		StopAllTasks();
}

task ultraSonic(){
	while(true){
	while(SensorValue(sonarSensor) <= 50){
	turn();
	}
}
}

task main()
{
	StartTask(stopMyTask);
	StartTask(ultraSonic);

  wait1Msec(2000);      

  int threshold = 2150;     
                            
  while(true)
  {
    displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
    displayLCDPos(1,0);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(lineFollowerLEFT));    //  Readings  |
    displayLCDPos(1,6);                                     //  to LCD.   |
    displayNextLCDNumber(SensorValue(lineFollowerCENTER));  //            |
    displayLCDPos(1,12);                                    //  L  C  R   |
    displayNextLCDNumber(SensorValue(lineFollowerRIGHT));   //  x  x  x   |

    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      motor[leftMotor]  = 63;
      motor[rightMotor] = 63;
    }
    else if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
    else if(SensorValue(lineFollowerLEFT) > threshold)
    {
      motor[leftMotor]  = 63;
      motor[rightMotor] = 0;
    }
  }
