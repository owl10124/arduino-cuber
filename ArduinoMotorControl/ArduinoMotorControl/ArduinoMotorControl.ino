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

#define SlideDist 4000
#define MaxSpeed 50000
#define MaxAccel 25000
#define TurnDist 400

// Define a stepper and the pins it will use
AccelStepper frontTurn(1, 22, 3);
AccelStepper frontSlide(1, 23, 4);
AccelStepper backTurn(1, 24, 5);
AccelStepper backSlide(1, 25, 6);
AccelStepper leftTurn(1, 26, 7);
AccelStepper leftSlide(1, 27, 8);
AccelStepper rightTurn(1, 28, 9);
AccelStepper rightSlide(1, 29, 10);

char chSequence[40];
int nCounter, nTotalStep;

void setup()
{
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

  //initMotors();

  Serial.begin(19200);
  Serial.print("ready");
}

void loop()
{
  while (true)
  {
	  nTotalStep = 0;
    if (Serial.available() > 0)
    {
	  delay(100);
      nTotalStep = Serial.available();

      for (int x = 0; x < nTotalStep; x++)
      {
        chSequence[x] = Serial.read();
      }
    }

    for (nCounter = 0; nCounter < nTotalStep;)
    {
      switch (chSequence[nCounter])
      {
      case 'A':
        frontClockwise();
        break;

      case 'B':
        frontAnticlockwise();
        break;

      case 'C':
        backClockwise();
        break;

      case 'D':
        backAnticlockwise();
        break;

      case 'E':
        leftClockwise();
        break;

      case 'F':
        leftAnticlockwise();
        break;

      case 'G':
        rightClockwise();
        break;

      case 'H':
        rightAnticlockwise();
        break;
      }
    }
  }
}

void initMotors()
{
  frontSlide.moveTo(-100000);
  while (digitalRead(FrontSw) == LOW)
  {
    frontSlide.run();
  }
  frontSlide.move(600);

  backSlide.moveTo(-100000);
  while (digitalRead(FrontSw) == LOW)
  {
    backSlide.run();
  }
  backSlide.move(600);


  leftSlide.moveTo(-100000);
  while (digitalRead(FrontSw) == LOW)
  {
    leftSlide.run();
  }
  leftSlide.move(600);

  rightSlide.moveTo(-100000);
  while (digitalRead(FrontSw) == LOW)
  {
    rightSlide.run();
  }
  rightSlide.move(600);
}

void frontClockwise()
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
  } while (chSequence[nCounter] == 'A');

  frontSlide.move(-SlideDist);
  frontSlide.runToPosition();

  frontTurn.move(-TurnDist * n);
  frontTurn.runToPosition();

  frontSlide.move(SlideDist);
  frontSlide.runToPosition();
}

void frontAnticlockwise()
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
  } while (chSequence[nCounter] == 'B');

  frontSlide.move(-SlideDist);
  frontSlide.runToPosition();

  frontTurn.move(TurnDist * n);
  frontTurn.runToPosition();

  frontSlide.move(SlideDist);
  frontSlide.runToPosition();
}

void backClockwise()
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
  } while (chSequence[nCounter] == 'C');

  backSlide.move(-SlideDist);
  backSlide.runToPosition();

  backTurn.move(-TurnDist * n);
  backTurn.runToPosition();

  backSlide.move(SlideDist);
  backSlide.runToPosition();
}

void backAnticlockwise()
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
  } while (chSequence[nCounter] == 'D');

  backSlide.move(-SlideDist);
  backSlide.runToPosition();

  backTurn.move(TurnDist * n);
  backTurn.runToPosition();

  backSlide.move(SlideDist);
  backSlide.runToPosition();
}

void leftClockwise()
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
  } while (chSequence[nCounter] == 'E');

  leftSlide.move(-SlideDist);
  leftSlide.runToPosition();

  leftTurn.move(-TurnDist * n);
  leftTurn.runToPosition();

  leftSlide.move(SlideDist);
  leftSlide.runToPosition();
}

void leftAnticlockwise()
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
  } while (chSequence[nCounter] == 'F');

  leftSlide.move(-SlideDist);
  leftSlide.runToPosition();

  leftTurn.move(TurnDist * n);
  leftTurn.runToPosition();

  leftSlide.move(SlideDist);
  leftSlide.runToPosition();
}

void rightClockwise()
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
  } while (chSequence[nCounter] == 'G');

  rightSlide.move(-SlideDist);
  rightSlide.runToPosition();

  rightTurn.move(-TurnDist * n);
  rightTurn.runToPosition();

  rightSlide.move(SlideDist);
  rightSlide.runToPosition();
}

void rightAnticlockwise()
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
  } while (chSequence[nCounter] == 'H');

  rightSlide.move(-SlideDist);
  rightSlide.runToPosition();

  rightTurn.move(TurnDist * n);
  rightTurn.runToPosition();

  rightSlide.move(SlideDist);
  rightSlide.runToPosition();
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


