#pragma config(Sensor, S1,     Eyes,           sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     Laser,          sensorEV3_Color)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, encoder)

void turnLeft(){
		setMotorSpeed(RightMotor, 30);
		setMotorSpeed(LeftMotor, 0);
}

void turnRight(){
	setMotorSpeed(RightMotor, 0);
	setMotorSpeed(LeftMotor, 30);
}

void checkDistance(){
	//Checking to see if object is within 10 CM
	//resetGyro(S3);
	if(getUSDistance(Eyes) < 10) {
		setMotorSpeed(RightMotor, -30);
				setMotorSpeed(LeftMotor, 30);
	}
    sleep(400);
}

task main() {
	while(true) {

		if(getColorName(Laser) == colorGreen) {
            checkDistance();
			turnRight();
			writeDebugStreamLine("GREEN");
        //Since the 'colorBlue' keyword doesn't work, check for the absence of white and green.
		} else if((getColorName(Laser) != colorGreen) && (getColorName(Laser) != colorWhite)) {
            checkDistance();
			turnRight();
			writeDebugStreamLine("BLUE");
		} else {
            checkDistance();
			turnLeft();
			writeDebugStreamLine("WHITE");
		}
	}
}