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
	while(SensorValue[stopButton] == 0 && vexRT[Btn7L]==0){ //medan ekki er itt a takka gerist ekki, annars keirir stopalltasks
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

  wait1Msec(2000);          // The program waits for 2000 milliseconds before continuing.

  int threshold = 2150;      /* found by taking a reading on both DARK and LIGHT    */
                            /* surfaces, adding them together, then dividing by 2. */
  while(true)
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
    displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
    displayLCDPos(1,0);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(lineFollowerLEFT));    //  Readings  |
    displayLCDPos(1,6);                                     //  to LCD.   |
    displayNextLCDNumber(SensorValue(lineFollowerCENTER));  //            |
    displayLCDPos(1,12);                                    //  L  C  R   |
    displayNextLCDNumber(SensorValue(lineFollowerRIGHT));   //  x  x  x   |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+

		// CENTER sensor sees dark:
    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      // go straight
      motor[leftMotor]  = 63;
      motor[rightMotor] = 63;
    }
    // RIGHT sensor sees dark:
    else if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
    // LEFT sensor sees dark:
    else if(SensorValue(lineFollowerLEFT) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 63;
      motor[rightMotor] = 0;
    }
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
