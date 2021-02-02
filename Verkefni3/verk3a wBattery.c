#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl1,  sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in2,    lightSensor,         sensorReflection)
#pragma config(Sensor, dgtl9,  stopButton,     sensorTouch)
#pragma config(Motor,  port1,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)

int power = 127;

task stopMyTask(){
	while(SensorValue[stopButton] == 0 && vexRT[Btn7L]==0){ //medan ekki er itt a takka gerist ekki, annars keirir stopalltasks
		}
		StopAllTasks();
}

task battery()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
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
	StartTask(battery);

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
