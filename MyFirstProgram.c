#pragma config(Sensor, S1,     Eyes,           sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     Laser,          sensorEV3_Color)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void turnLeft(){
	setMotorSpeed(RightMotor, 10);
	setMotorSpeed(LeftMotor, 0);
}

void turnRight(){
	setMotorSpeed(RightMotor, 0);
	setMotorSpeed(LeftMotor, 10);
}

void checkDistance(int n){
	//Checking to see if object is within 10 CM
	//resetGyro(S3);

	if(getUSDistance(Eyes) < 10) {
		if (getColorName(Laser) == colorGreen){
			n = 1;
		} else if (getColorName(Laser) != colorGreen && getColorName(Laser) != colorWhite){
			n = 2;
		}
		if(n == 1) {
			setMotorSpeed(RightMotor, 0);
			setMotorSpeed(LeftMotor, 0);

			playTone(440, 200);
			playTone(440, 20);
			sleep(2000);

			setMotorSpeed(RightMotor, 50);
			setMotorSpeed(LeftMotor, -50);
			sleep(800);
		} else if(n == 2){
			setMotorSpeed(RightMotor, 0);
			setMotorSpeed(LeftMotor, 0);
			playTone(587, 20);
			sleep(2000);

			setMotorSpeed(RightMotor, -100);
			setMotorSpeed(LeftMotor, 100);
			sleep(600);
			setMotorSpeed(RightMotor, 100);
			setMotorSpeed(LeftMotor, -100);
			sleep(600);
			sleep(100);
		}
	}
}

task main() {

	/*while((getColorName(Laser) == colorGreen) || ((getColorName(Laser) != colorGreen) && (getColorName(Laser) != colorWhite))) {
		setMotorSpeed(RightMotor, 100);
		setMotorSpeed(LeftMotor, 100);
	}*/
	int n;
	double Kp = 0.5;
	double Ki = 0.0336;
	double Kd = 2.67;
	double offset = 27;
	double Tp = 7;
	double lightValue;
	double powerLeft;
	double powerRight;
	double error;
	double Turn;

	double derivative = 0;
	double lastError = 0;
	double integral = 0;

	double powerLeftMax = 20;
	double powerRightMax = 20;
	double powerLeftmin = -20;
	double powerRightmin = -20;
	double deltaTime = 0.014;
	//ClearTimer(T1);

	while(true) {
		lightValue = getColorReflected(Laser);
		error = lightValue - offset;
		integral = integral + (error)* deltaTime;
		derivative = (error - lastError)/ deltaTime;
//		Turn = Kp * error + Ki * integral + Kd * derivative;
		Turn = Kp * error;

		powerLeft = Tp - Turn;
		powerRight = Tp + Turn;

		if (powerLeft > powerLeftMax){
			powerLeft = powerLeftMax;
		}
		if (powerLeft < powerLeftMin){
			powerLeft = powerLeftMin;
		}
		if (powerRight > powerRightMax){
			powerRight = powerRightMax;
		}
		if (powerRight > powerRightMax){
			powerRight = powerRightmin;
		}
		checkDistance(n);
		setMotorSpeed(LeftMotor, powerLeft);
		setMotorSpeed(RightMotor, powerRight);
		lastError = error;

		//if we are on green
		//The value will be less
		//This means error will be ... negative
		//If error is negative --> we want to go left

	//}

		//First PID Algorithm
		/*if (getColorReflected(Laser) >= 40){
			turnLeft();
		} else if ((getColorReflected(Laser) > 10) && (40 > getColorReflected(Laser))){
			setMotorSpeed(RightMotor, 10);
			setMotorSpeed(LeftMotor, 10);
		}
		else {
			turnRight();
		}*






		/*if(getColorName(Laser) == colorGreen) {
			n = 1;
      checkDistance(n);
			turnRight();
			//writeDebugStreamLine("GREEN");
        //Since the 'colorBlue' keyword doesn't work, check for the absence of white and green.
		//} else if((getColorName(Laser) != colorGreen) && (getColorName(Laser) != colorWhite)) {
		else if((getColorName(Laser) != colorGreen) && (getColorName(Laser) != colorWhite)) {
			n = 2;//blue line
      checkDistance(n);
			turnRight();
			//writeDebugStreamLine("BLUE");
		} else {
			n = 3;
      checkDistance(n);
			turnLeft();
			//writeDebugStreamLine("WHITE");
		}*/
	}
}
