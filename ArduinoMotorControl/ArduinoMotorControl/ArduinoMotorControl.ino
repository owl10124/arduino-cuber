/*
 Name:    ArduinoMotorControl.ino
 Created: 6/8/2017 9:12:15 PM
 Author:  LINJING
*/

#include <Stepper.h>
#include <AccelStepper.h>

#define FrontSw 31
#define BackSw 32
#define LeftSw 33
#define RightSw 34

#define FrontRst A0
#define BackRst A1
#define LeftRst A2
#define RightRst A3

#define SlideDist 4000
#define MaxSpeed 50000
#define MaxAccel 25000
#define TurnDist 400

#define CalibrationDist -20000
#define FullTurn 1600
#define TrigPoint 512

#define FRONTTURN 0
#define FRONTSLIDE 1
#define BACKTURN 2
#define BACKSLIDE 3
#define LEFTTURN 4
#define LEFTSLIDE 5
#define RIGHTTURN 6
#define RIGHTSLIDE 7

#define GoClockwise 0
#define GoAntiClockwise 1
										

// Define a stepper and the pins it will use
AccelStepper frontTurn(1, 22, 3);
AccelStepper frontSlide(1, 23, 4);
AccelStepper backTurn(1, 24, 5);
AccelStepper backSlide(1, 25, 6);
AccelStepper leftTurn(1, 26, 7);
AccelStepper leftSlide(1, 27, 8);
AccelStepper rightTurn(1, 28, 9);
AccelStepper rightSlide(1, 29, 10);

AccelStepper *pmotor[8];

char chSequence[40];
char chSerial[1000];
int nCounter, nTotalStep;

void setup()
{
	bool bHandshake = false;

	pmotor[FRONTTURN] = &frontTurn;
	pmotor[FRONTSLIDE] = &frontSlide;
	pmotor[BACKTURN] = &backTurn;
	pmotor[BACKSLIDE] = &backSlide;
	pmotor[LEFTTURN] = &leftTurn;
	pmotor[LEFTSLIDE] = &leftSlide;
	pmotor[RIGHTTURN] = &rightTurn;
	pmotor[RIGHTSLIDE] = &rightSlide;

	// Change these to suit your stepper if you want
	frontTurn.setEnablePin(30);
	frontTurn.setMaxSpeed(MaxSpeed);
	frontTurn.setAcceleration(MaxAccel);

	frontSlide.setEnablePin(31);
	frontSlide.setMaxSpeed(MaxSpeed);
	frontSlide.setAcceleration(MaxAccel);

	backTurn.setEnablePin(32);
	backTurn.setMaxSpeed(MaxSpeed);
	backTurn.setAcceleration(MaxAccel);

	backSlide.setEnablePin(33);
	backSlide.setMaxSpeed(MaxSpeed);
	backSlide.setAcceleration(MaxAccel);

	leftTurn.setEnablePin(34);
	leftTurn.setMaxSpeed(MaxSpeed);
	leftTurn.setAcceleration(MaxAccel);

	leftSlide.setEnablePin(35);
	leftSlide.setMaxSpeed(MaxSpeed);
	leftSlide.setAcceleration(MaxAccel);

	rightTurn.setEnablePin(36);
	rightTurn.setMaxSpeed(MaxSpeed);
	rightTurn.setAcceleration(MaxAccel);

	rightSlide.setEnablePin(37);
	rightSlide.setMaxSpeed(MaxSpeed);
	rightSlide.setAcceleration(MaxAccel);

	pinMode(FrontSw, INPUT);
	pinMode(BackSw, INPUT);
	pinMode(LeftSw, INPUT);
	pinMode(RightSw, INPUT);

	pinMode(FrontRst, INPUT);
	pinMode(BackRst, INPUT);
	pinMode(LeftRst, INPUT);
	pinMode(RightRst, INPUT);

	while (bHandshake == false)
	{
		Serial.begin(28800);
		Serial.print("ready");
		delay(1000);

		if (Serial.available() > 0)
		{
			delay(150);
			nTotalStep = Serial.available();

			for (int x = 0; x < nTotalStep; x++)
			{
				chSerial[x] = Serial.read();
			}

			if (chSerial == "pi_is_ready")
				bHandshake = true;
		}
	}

	initMotors();
}

void loop()
{


	while (true)
	{
		nTotalStep = 0;
		if (Serial.available() > 0)
		{
			delay(150);
			nTotalStep = Serial.available();

			for (int x = 0; x < nTotalStep; x++)
			{
				chSequence[x] = Serial.read();
			}
		}

		if (CheckCommand() == 1)
			break;

		for (nCounter = 0; nCounter < nTotalStep;)
		{
			switch (chSequence[nCounter])
			{
				case 'A':
					topClockwise();
					break;

				case 'B':
					topAnticlockwise();
					break;

				case 'C':
					bottomClockwise();
					break;

				case 'D':
					bottomAnticlockwise();
					break;

				case 'E':
					frontClockwise();
					break;

				case 'F':
					frontAnticlockwise();
					break;

				case 'G':
					backClockwise();
					break;

				case 'H':
					backAnticlockwise();
					break;

				case 'I':
					leftClockwise();
					break;

				case 'J':
					leftAnticlockwise();
					break;

				case 'K':
					rightClockwise();
					break;

				case 'L':
					rightAnticlockwise();
					break;
			}
		}
	}
}

int ScanCube()
{

}

int CheckCommand()
{
	for (nCounter = 0; nCounter < nTotalStep;)
	{
		switch (chSequence[nCounter])
		{
		case 'A':
			break;

		case 'B':
			break;

		case 'C':
			break;

		case 'D':
			break;

		case 'E':
			break;

		case 'F':
			break;

		case 'G':
			break;

		case 'H':
			break;

		case 'I':
			break;

		case 'J':
			break;

		case 'K':
			break;

		case 'L':
			break;

		default:
			Serial.println("redo");
			Serial.println("Bad Command Sequence Given");
			Serial.println("Error: Aborting");
			return 1;
		}
	}
	
	return 0;
}

void initMotors()
{
	frontSlide.move(100000000);
	while (digitalRead(FrontSw) == LOW)
	{
		frontSlide.run();
	}
	frontSlide.setCurrentPosition(0);

	backSlide.move(100000000);
	while (digitalRead(BackSw) == LOW)
	{
		backSlide.run();
	}
	backSlide.setCurrentPosition(0);

	leftSlide.move(100000000);
	while (digitalRead(LeftSw) == LOW)
	{
		leftSlide.run();
	}
	leftSlide.setCurrentPosition(0);

	rightSlide.move(100000000);
	while (digitalRead(RightSw) == LOW)
	{
		rightSlide.run();
	}
	rightSlide.setCurrentPosition(0);

	frontTurn.move(FullTurn);
	while (analogRead(FrontRst) >= TrigPoint)
	{
		frontTurn.run();
	}
	frontTurn.setCurrentPosition(0);

	backTurn.move(FullTurn);
	while (analogRead(BackRst) >= TrigPoint)
	{
		backTurn.run();
	}
	backTurn.setCurrentPosition(0);
		
	leftTurn.move(FullTurn);
	while (analogRead(LeftRst) >= TrigPoint)
	{
		leftTurn.run();
	}
	leftTurn.setCurrentPosition(0);

	rightTurn.move(FullTurn);
	while (analogRead(RightRst) >= TrigPoint)
	{
		rightTurn.run();
	}
	rightTurn.setCurrentPosition(0);
  //frontSlide.move(CalibrationDist);
  //frontSlide.runToPosition();
  //while (digitalRead(FrontSw) == LOW)
  //{
  //  frontSlide.run();
  //}
  //frontSlide.move(SlideDist);

  //backSlide.move(CalibrationDist);
  //backSlide.runToPosition();
  //while (digitalRead(FrontSw) == LOW)
  //{
  //  backSlide.run();
  //}
  //backSlide.move(SlideDist);


  //leftSlide.move(CalibrationDist);
  //leftSlide.runToPosition();
  //while (digitalRead(FrontSw) == LOW)
  //{
  //  leftSlide.run();
  //}
  //leftSlide.move(SlideDist);

  //rightSlide.move(CalibrationDist);
  //while (digitalRead(FrontSw) == LOW)
  //{
  //  rightSlide.run();
  //}
  //rightSlide.move(SlideDist);
}

void frontClockwise()
{
  int n = 0;
  do
  {
    frontTurn.move(-TurnDist);
	frontTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'E');

  frontSlide.move(-SlideDist);
  frontSlide.runToPosition();

  frontTurn.move(TurnDist * n);
  frontTurn.runToPosition();

  frontSlide.move(SlideDist);
  frontSlide.runToPosition();
}

void frontAnticlockwise()
{
  int n = 0;
  do
  {
    frontTurn.move(TurnDist);
	frontTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'F');

  frontSlide.move(-SlideDist);
  frontSlide.runToPosition();

  frontTurn.move(-TurnDist * n);
  frontTurn.runToPosition();

  frontSlide.move(SlideDist);
  frontSlide.runToPosition();
}

void backClockwise()
{
  int n = 0;
  do
  {
    backTurn.move(-TurnDist);
	backTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'G');

  backSlide.move(-SlideDist);
  backSlide.runToPosition();

  backTurn.move(TurnDist * n);
  backTurn.runToPosition();

  backSlide.move(SlideDist);
  backSlide.runToPosition();
}

void backAnticlockwise()
{
  int n = 0;
  do
  {
    backTurn.move(TurnDist);
	backTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'H');

  backSlide.move(-SlideDist);
  backSlide.runToPosition();

  backTurn.move(-TurnDist * n);
  backTurn.runToPosition();

  backSlide.move(SlideDist);
  backSlide.runToPosition();
}

void leftClockwise()
{
  int n = 0;
  do
  {
    leftTurn.move(-TurnDist);
	leftTurn.runToPosition();

    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'I');

  leftSlide.move(-SlideDist);
  leftSlide.runToPosition();

  leftTurn.move(TurnDist * n);
  leftTurn.runToPosition();

  leftSlide.move(SlideDist);
  leftSlide.runToPosition();
}

void leftAnticlockwise()
{
  int n = 0;
  do
  {
    leftTurn.move(TurnDist);
	leftTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'J');

  leftSlide.move(-SlideDist);
  leftSlide.runToPosition();

  leftTurn.move(-TurnDist * n);
  leftTurn.runToPosition();

  leftSlide.move(SlideDist);
  leftSlide.runToPosition();
}

void rightClockwise()
{
  int n = 0;
  do
  {
    rightTurn.move(-TurnDist);
	rightTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'K');

  rightSlide.move(-SlideDist);
  rightSlide.runToPosition();

  rightTurn.move(TurnDist * n);
  rightTurn.runToPosition();

  rightSlide.move(SlideDist);
  rightSlide.runToPosition();
}

void rightAnticlockwise()
{
  int n = 0;
  do
  {
    rightTurn.move(TurnDist);
	rightTurn.runToPosition();
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'L');

  rightSlide.move(-SlideDist);
  rightSlide.runToPosition();

  rightTurn.move(-TurnDist * n);
  rightTurn.runToPosition();

  rightSlide.move(SlideDist);
  rightSlide.runToPosition();
}

void topClockwise()
{
	int n = 0;

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);

	do
	{
		frontTurn.move(-TurnDist);
		frontTurn.runToPosition();
		nCounter++;
		if (nCounter > nTotalStep)
			break;
		n++;
	} while (chSequence[nCounter] == 'A');

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);

	frontTurn.move(n * TurnDist);
	frontTurn.runToPosition();

	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
}

void topAnticlockwise()
{
	int n = 0;

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);

	do
	{
		backTurn.move(-TurnDist);
		backTurn.runToPosition();
		nCounter++;
		if (nCounter > nTotalStep)
			break;
		n++;
	} while (chSequence[nCounter] == 'B');

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);

	backTurn.move(n * TurnDist);
	backTurn.runToPosition();

	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
}

void bottomClockwise()
{
	int n = 0;

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);

	do
	{
		frontTurn.move(-TurnDist);
		frontTurn.runToPosition();
		nCounter++;
		if (nCounter > nTotalStep)
			break;
		n++;
	} while (chSequence[nCounter] == 'C');

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);

	frontTurn.move(n * TurnDist);
	frontTurn.runToPosition();

	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
}

void bottomAnticlockwise()
{
	int n = 0;

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);

	do
	{
		backTurn.move(-TurnDist);
		backTurn.runToPosition();
		nCounter++;
		if (nCounter > nTotalStep)
			break;
		n++;
	} while (chSequence[nCounter] == 'D');

	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);

	backTurn.move(n * TurnDist);
	backTurn.runToPosition();

	TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
	SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
}

void SlideTwoMotors(byte Motor1, byte Motor2, byte Direction, int nSteps)
{
	if (Motor1 == Motor2)
		return;

	if (Direction > GoAntiClockwise && Direction > GoClockwise)
		return;

	if (Direction == 0 && Direction != 1)
	{
		pmotor[Motor1]->move(nSteps);
		pmotor[Motor2]->move(nSteps);
	}
	else
	{
		pmotor[Motor1]->move(-nSteps);
		pmotor[Motor2]->move(-nSteps);
	}

	while (pmotor[Motor1]->distanceToGo() > 0 || pmotor[Motor2]->distanceToGo() > 0)
	{
		pmotor[Motor1]->run();
		pmotor[Motor2]->run();
	}
}

void TurnTwoMotors(byte Motor1, byte Motor2, byte Direction, int nSteps)
{
	if (Motor1 == Motor2)
		return;

	if (Direction > GoAntiClockwise && Direction > GoClockwise)
		return;

	if (Direction == 0 && Direction != 1)
	{
		pmotor[Motor1]->move(nSteps);
		pmotor[Motor2]->move(-nSteps);
	}
	else
	{
		pmotor[Motor1]->move(-nSteps);
		pmotor[Motor2]->move(nSteps);
	}

	while (pmotor[Motor1]->distanceToGo() > 0 || pmotor[Motor2]->distanceToGo() > 0)
	{
		pmotor[Motor1]->run();
		pmotor[Motor2]->run();
	}
}

//void topClockwise()
//{
//  int n = 0;
//  
//  leftSlide.moveTo(leftSlide.currentPosition() - 200);
//  rightSlide.moveTo(rightSlide.currentPosition() - 200);
//
//  while (leftSlide.distanceToGo() > 0 || rightSlide.distanceToGo() > 0)   // pulls the left and right motors away from the cube
//  {
//    leftSlide.run();
//    rightSlide.run();
//  }
//
//  frontTurn.moveTo(frontTurn.currentPosition() - 50);
//  backTurn.moveTo(backTurn.currentPosition() - 50);
//
//  while (frontTurn.distanceToGo() > 0 || backTurn.distanceToGo() > 0)   // turns the top face over to the left side
//  {
//    frontTurn.run();
//    backTurn.run();
//  }
//
//  leftSlide.moveTo(leftSlide.currentPosition() + 200);
//  rightSlide.moveTo(rightSlide.currentPosition() + 200);
//
//  while (leftSlide.distanceToGo() > 0 || rightSlide.distanceToGo() > 0)   // puts the left and right motors back towards the cube
//  {
//    leftSlide.run();
//    rightSlide.run();
//  }
//
//  do
//  {
//    leftTurn.move(50);
//    nCounter++;
//    if (nCounter > nTotalStep)
//      break;
//    n++;
//  } while (chSequence[nCounter] == 'A');
//
//  leftSlide.moveTo(leftSlide.currentPosition() - 200);
//  rightSlide.moveTo(rightSlide.currentPosition() - 200);
//
//  while (leftSlide.distanceToGo() > 0 || rightSlide.distanceToGo() > 0)   // pulls the left and right motors away from the cube
//  {
//    leftSlide.run();
//    rightSlide.run();
//  }
//
//  frontTurn.moveTo(frontTurn.currentPosition() + 50);
//  backTurn.moveTo(backTurn.currentPosition() + 50);
//
//  while (frontTurn.distanceToGo() > 0 || backTurn.distanceToGo() > 0)   // turns the top face over to the left side
//  {
//    frontTurn.run();
//    backTurn.run();
//  }
//
//  leftSlide.moveTo(leftSlide.currentPosition() + 200);
//  rightSlide.moveTo(rightSlide.currentPosition() + 200);
//
//  while (leftSlide.distanceToGo() > 0 || rightSlide.distanceToGo() > 0)   // pulls the left and right motors away from the cube
//  {
//    leftSlide.run();
//    rightSlide.run();
//  }
//
//}


