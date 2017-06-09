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

// Define a stepper and the pins it will use
AccelStepper frontTurn(1, 3, 14);
AccelStepper frontSlide(1, 4, 15);
AccelStepper backTurn(1, 5, 16);
AccelStepper backSlide(1, 6, 17);
AccelStepper leftTurn(1, 7, 18);
AccelStepper leftSlide(1, 8, 19);
AccelStepper rightTurn(1, 9, 20);
AccelStepper rightSlide(1, 10, 21);

char chSequence[30];
int nCounter, nTotalStep;

void setup()
{
  // Change these to suit your stepper if you want
  frontTurn.setEnablePin(23);
  frontTurn.setMaxSpeed(2000);
  frontTurn.setAcceleration(2000);

  frontSlide.setEnablePin(24);
  frontSlide.setMaxSpeed(2000);
  frontSlide.setAcceleration(2000);

  backTurn.setEnablePin(25);
  backTurn.setMaxSpeed(2000);
  backTurn.setAcceleration(2000);

  backSlide.setEnablePin(26);
  backSlide.setMaxSpeed(2000);
  backSlide.setAcceleration(2000);

  leftTurn.setEnablePin(27);
  leftTurn.setMaxSpeed(2000);
  leftTurn.setAcceleration(2000);

  leftSlide.setEnablePin(28);
  leftSlide.setMaxSpeed(2000);
  leftSlide.setAcceleration(2000);

  rightTurn.setEnablePin(29);
  rightTurn.setMaxSpeed(2000);
  rightTurn.setAcceleration(2000);

  rightSlide.setEnablePin(30);
  rightSlide.setMaxSpeed(2000);
  rightSlide.setAcceleration(2000);

  pinMode(FrontSw, INPUT);
  pinMode(BackSw, INPUT);
  pinMode(LeftSw, INPUT);
  pinMode(RightSw, INPUT);

  initMotors();

  Serial.begin(19200);
  Serial.print("ready");
}

void loop()
{
  while (true)
  {
    if (Serial.available() > 0)
    {
      nTotalStep = Serial.available();

      for (int x = 0; x <= nTotalStep; x++)
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

      case 'B':
        frontAnticlockwise();

      case 'C':
        backClockwise();

      case 'D':
        backAnticlockwise();

      case 'E':
        leftClockwise();

      case 'F':
        leftAnticlockwise();

      case 'G':
        rightClockwise();

      case 'H':
        rightAnticlockwise();
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
    frontTurn.move(50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'A');

  frontSlide.move(-200);
  frontTurn.move(-50 * n);
  frontSlide.move(200);
}

void frontAnticlockwise()
{
  int n = 0;
  do
  {
    frontTurn.move(-50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'B');

  frontSlide.move(-200);
  frontTurn.move(50 * n);
  frontSlide.move(200);
}

void backClockwise()
{
  int n = 0;
  do
  {
    backTurn.move(50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'C');

  backSlide.move(-200);
  backTurn.move(-50 * n);
  backSlide.move(200);
}

void backAnticlockwise()
{
  int n = 0;
  do
  {
    backTurn.move(-50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'D');

  backSlide.move(-200);
  backTurn.move(50 * n);
  backSlide.move(200);
}

void leftClockwise()
{
  int n = 0;
  do
  {
    leftTurn.move(50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'E');

  leftSlide.move(-200);
  leftTurn.move(-50 * n);
  leftSlide.move(200);
}

void leftAnticlockwise()
{
  int n = 0;
  do
  {
    leftTurn.move(-50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'F');

  leftSlide.move(-200);
  leftTurn.move(50 * n);
  leftSlide.move(200);
}

void rightClockwise()
{
  int n = 0;
  do
  {
    rightTurn.move(50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'G');

  rightSlide.move(-200);
  rightTurn.move(-50 * n);
  rightSlide.move(200);
}

void rightAnticlockwise()
{
  int n = 0;
  do
  {
    rightTurn.move(-50);
    nCounter++;
    if (nCounter > nTotalStep)
      break;
    n++;
  } while (chSequence[nCounter] == 'H');

  rightSlide.move(-200);
  rightTurn.move(50 * n);
  rightSlide.move(200);
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


