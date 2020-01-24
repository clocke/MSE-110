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

void checkDistance(int n){
	//Checking to see if object is within 10 CM
	//resetGyro(S3);
	if(getUSDistance(Eyes) < 10) {
		if(n == 1) {
			setMotorSpeed(RightMotor, 0);
			setMotorSpeed(LeftMotor, 0);

			playTone(440, 20);
			sleep(2000);

			setMotorSpeed(RightMotor, 50);
			setMotorSpeed(LeftMotor, -50);
			sleep(900);
		} else if(n == 2){
			setMotorSpeed(RightMotor, 0);
			setMotorSpeed(LeftMotor, 0);
			playTone(587, 20);
			sleep(2000);

			setMotorSpeed(RightMotor, -100);
			setMotorSpeed(LeftMotor, 100);
			sleep(100);
		}
	}
}

task main() {
	while(true) {
		int n;
		if(getColorName(Laser) == colorGreen) {
			n = 1;
      checkDistance(n);
			turnRight();
			//writeDebugStreamLine("GREEN");
        //Since the 'colorBlue' keyword doesn't work, check for the absence of white and green.
		} else if((getColorName(Laser) != colorGreen) && (getColorName(Laser) != colorWhite)) {
			n = 2;//blue line
      checkDistance(n);
			turnRight();
			//writeDebugStreamLine("BLUE");
		} else {
			n = 3;
      checkDistance(n);
			turnLeft();
			//writeDebugStreamLine("WHITE");
		}
	}
}