/*
 Name:    ArduinoMotorControl.ino
 Created: 6/8/2017 9:12:15 PM
 Author:  LINYICHENG
*/

#include <string.h>
#include <Stepper.h>
#include <AccelStepper.h>

#define tolerance FullTurn/16
#define calibration FullTurn/1600 * 10

#define MotorCalSw 40
#define StartSw 42
#define HoldCubeSw 44

#define FrontSw 47
#define BackSw 44
#define LeftSw 45
#define RightSw 46

#define FrontRst A0
#define BackRst A3
#define LeftRst A2
#define RightRst A1

#define CalibrationDist -20000
#define FullTurn 1600
#define TrigPoint 900

#define SlideDist FullTurn/4 * 6
#define MaxSpeed 80000
#define MaxAccel 50000
#define TurnDist FullTurn/4

#define FRONTTURN 0
#define FRONTSLIDE 1
#define BACKTURN 2
#define BACKSLIDE 3
#define LEFTTURN 4
#define LEFTSLIDE 5
#define RIGHTTURN 6
#define RIGHTSLIDE 7
#define TOTAL_MOTORS 8

#define GoClockwise 0
#define GoAntiClockwise 1

#define MAX_TURN_STEPS 400
#define MAX_SERIAL_LENGTH 1000

// Define a stepper and the pins it will use
// first number specifies the state, in this case 1 means driver state
//second number is the PUL pin the third one is the DIR pin
AccelStepper frontTurn(1, 22, 3);
AccelStepper frontSlide(1, 23, 4);
AccelStepper backTurn(1, 24, 5);
AccelStepper backSlide(1, 25, 6);
AccelStepper leftTurn(1, 26, 7);
AccelStepper leftSlide(1, 27, 8);
AccelStepper rightTurn(1, 28, 9);
AccelStepper rightSlide(1, 29, 10);

AccelStepper *pmotor[8];

char chSequence[MAX_TURN_STEPS];
char chSerial[MAX_SERIAL_LENGTH + 1];    // Extra one char for terminator of string 0x00
int nCounter, nTotalStep, nTotalChar;

int StartSwState = 0;         // current state of the Start button
int lastStartSwState = 0;
int CalSwState = 0;         // current state of the Motor Calibration button
int lastCalSwState = 0;
int HoldSwState = 0;         // current state of the Hold Cube button
int lastHoldSwState = 0;

bool bHoldCube = false;   // false menas currently cube is not hold on the jig

// this initializes the chars used for serial protocol
char* pchGO = "GO";
char* pchDoneSide = "done_side";

void setup()
{
  bool bHandshake = false;

  // this initializes the array of stepper motors, for easy 
  // reference in the TurnTwoMotors and SlideTwoMotors functions
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

  pinMode(MotorCalSw, INPUT);
  pinMode(StartSw, INPUT);
  pinMode(HoldCubeSw, INPUT);

  Serial.begin(115200);  // Set serial port communication baund rate
  Serial3.begin(115200);
  
  int ok = 0;
  while (ok < 20) {
    Serial3.print("test\n");
    delay(100);
    ok++;
  }

#if 1 
  // initiates a handshake with the raspberry pi
  delay(5000);
  while (!bHandshake)
  {
    Serial.print("ready\n");
    delay(1000);
    if (Serial.available() > 0)
    {
      delay(150);
      nTotalChar = Serial.available();
      if (nTotalChar > MAX_SERIAL_LENGTH)
        nTotalChar = MAX_SERIAL_LENGTH;
      int x;
      for (x = 0; x < (nTotalChar); x++)
      {
        chSerial[x] = Serial.read();
      }
      chSerial[x] = 0x00;
      char* pchPiIsReady = "pi_is_ready";
      if (strcmp(chSerial, pchPiIsReady)==0)
        bHandshake = true;
      else {Serial.print("aaaaaaaaaaaa\n");}
    }
  }
  // initializes the motors to correct positions
  initMotors();
#endif

}

void loop()
{
  // waits for trigger
  //while (digitalRead(StartSw) == LOW)
  //{
  //  if (digitalRead(MotorCalSw) == HIGH)
  //    initMotors();
  //}

  bool bStart = false;

#if 1
  bool bCalMotors = false;
  // read the pushbutton input pin:
  if (bHoldCube == true)
  {
    StartSwState = digitalRead(StartSw);
    // compare the buttonState to its previous state
    if (StartSwState != lastStartSwState)
    {
      // if the state has changed, increment the counter
      if (StartSwState == HIGH)
      {
        // if the current state is HIGH then the button
        // wend from off to on:
        bStart = false;
      }
      else if (StartSwState == LOW)
      {
        bStart = true;
      }
      // Delay a little bit to avoid bouncing
      delay(30);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastStartSwState = StartSwState;
  }
  if (bStart == false)
  {
    // read the pushbutton input pin:
    CalSwState = digitalRead(MotorCalSw);
    // compare the buttonState to its previous state
    if (CalSwState != lastCalSwState)
    {
      // if the state has changed, increment the counter
      if (CalSwState == HIGH)
      {
        // if the current state is HIGH then the button
        // wend from off to on:
        bStart = false;
        bCalMotors = false;
      }
      else if (CalSwState == LOW)
      {
        bCalMotors = true;
        initMotors();
        bCalMotors = false;
      }
      // Delay a little bit to avoid bouncing
      delay(30);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastCalSwState = CalSwState;
  }
  if (bCalMotors == false && bStart == false)
  {
    // read the pushbutton input pin:
    HoldSwState = digitalRead(HoldCubeSw);
    // compare the buttonState to its previous state
    if (HoldSwState != lastHoldSwState)
    {
      // if the state has changed, increment the counter
      if (HoldSwState == HIGH)
      {
        // if the current state is HIGH then the button
        // wend from off to on:
        bStart = false;
        bCalMotors = false;
      }
      else if (HoldSwState == LOW)
      {
        if (bHoldCube == false)
        {
          HoldCube(true);
          bHoldCube = true;
        }
        else if (bHoldCube == true)   // If currently cube is hold, then release it
        {
          HoldCube(false);      // Release cube
          bHoldCube = false;      // set status after release the cube
        }
      }
      // Delay a little bit to avoid bouncing
      delay(30);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastHoldSwState = CalSwState;
  }
  if (bStart == true && bHoldCube == true)
  {
    // communicates with the raspberry pi to scan the cube
    Serial3.print("Scanning cube");
    ScanCube();
#else
  bStart = true;
  ScanCube();
  if (1)
  {
#endif
    while (bStart == true)
    {
      // gets instructons from the raspberry pi
      nTotalStep = 0;
      while (!Serial.available()) true;
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalStep = Serial.available();

        for (int x = 0; x < nTotalStep; x++)
        {
          chSequence[x] = Serial.read();
        }
      }

      // checks for error in the transmitted commands
      if (CheckCommand() == 1)
        break;
  #if 1
      // executes the commands
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
#endif
#if 1
      HoldCube(false);
#endif
      bHoldCube = false;
      bStart = false;
    }
  }
}


//void ClearCharArray(char &chArray[])
//{
//  for (int w = 0; w < sizeof(chArray); w++)
//  {
//    chArray[w] = ' ';
//  }
//}

void HoldCube(bool Hold)
{
  if (Hold == false)
  {
    frontSlide.move(-SlideDist);
    backSlide.move(-SlideDist);
    leftSlide.move(-SlideDist);
    rightSlide.move(-SlideDist);
  }
  else if (Hold == true)
  {
    frontSlide.move(SlideDist);
    backSlide.move(SlideDist);
    leftSlide.move(SlideDist);
    rightSlide.move(SlideDist);
  }

  while (frontSlide.distanceToGo() > 0 || backSlide.distanceToGo() > 0 || leftSlide.distanceToGo() > 0 || rightSlide.distanceToGo() > 0)
  {
    frontSlide.run();
    backSlide.run();
    leftSlide.run();
    rightSlide.run();
  }
}

void ScanCube()
{
  // tells the pi to start scanning
  Serial.print("init_scan\n");
  delay(200);

  int nSides = 6;
  bool bSideDone = false;

  // check if pi confirms scan
  if (Serial.available() > 0)
  {
    delay(150);
    nTotalChar = Serial.available();
    if (nTotalChar > MAX_SERIAL_LENGTH)
      nTotalChar = MAX_SERIAL_LENGTH;

    int x;
    for (x = 0; x < nTotalChar; x++)
    {
      chSerial[x] = Serial.read();
    }

    chSerial[x] = 0x00;
  }


  if (strcmp(chSerial, pchGO) == 0)
  {
    #if 0
    SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
    TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);

    Serial.print("scan\n");

    int x;

    /*  this series of functions essentially requests an image to be taken
      and the waits for the pi to confirm the image was successfully taken
      then the arduino proceeds to move the next face to the pi cam for 
      the image to be taken.*/
    while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }

    TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist * 2);

    Serial.print("scan\n");

    while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }

    TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
    SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
    SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
    TurnTwoMotors(FRONTTURN, BACKTURN, GoClockwise, TurnDist);

    Serial.print("scan\n");

    while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }

    TurnTwoMotors(FRONTTURN, BACKTURN, GoClockwise, TurnDist * 2);

    Serial.print("scan\n");

    while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }

    TurnTwoMotors(FRONTTURN, BACKTURN, GoClockwise, TurnDist);
    SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
    SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
    TurnTwoMotors(FRONTTURN, BACKTURN, GoClockwise, TurnDist);
    SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
    SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);

    Serial.print("scan\n");
    while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }

    TurnTwoMotors(FRONTTURN, BACKTURN, GoClockwise, TurnDist * 2);

    Serial.print("scan\n");

    while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }

    TurnTwoMotors(FRONTTURN, BACKTURN, GoClockwise, TurnDist);
    SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
    SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
    TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
    SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
    SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
    TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
    SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
  #else
  int x;
  Serial.print("scan\nscan\nscan\nscan\nscan\nscan\n");
  for (int i=0;i<6;i++)
  {
  while (bSideDone == false)
    {
      if (Serial.available() > 0)
      {
        delay(150);
        nTotalChar = Serial.available();
        if (nTotalChar > MAX_SERIAL_LENGTH)
          nTotalChar = MAX_SERIAL_LENGTH;

        for (x = 0; x < nTotalChar; x++)
        {
          chSerial[x] = Serial.read();
        }

        chSerial[x] = 0x00;

        if (strcmp(chSerial, pchDoneSide) == 0)
        {
          bSideDone = true;
          nSides -= 1;
        }
      }
    }
    bSideDone=false;
  }
    #endif
  }
  return;
}

int CheckCommand()
{
  // checks for errors in the command by cycling it through a loop
  for (nCounter = 0; nCounter < nTotalStep;nCounter++)
  {
    if ((chSequence[nCounter] < 0x41) || (chSequence[nCounter] > 0x4C)) // 'A' = 0x41, 'L' = 0x4C
    {
      Serial.println("redo");
      Serial.println("Bad Command Sequence Given");
      Serial.println("Error: Aborting");
      return 1;
    }
#if 0
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
#endif
  }

  return 0;
}

void initMotors()
{
  Serial3.println("initMotors Starts!");

#if 0
  // initializes the bottom four slider motors
  // with input from the limit switches
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

  // resets the position of the four turning
  // motors on top using te data gathered
  // from the hall effect sensors
  frontTurn.move(FullTurn);
  while (analogRead(FrontRst) < TrigPoint)
  {
    frontTurn.run();
  }
  frontTurn.setCurrentPosition(0);
  //Serial.println("frontTurn Stopped!");

  backTurn.move(FullTurn);
  while (analogRead(BackRst) < TrigPoint)
  {
    backTurn.run();
  }
  backTurn.setCurrentPosition(0);
  //Serial.println("backTurn Stopped!");
   
  leftTurn.move(FullTurn);
  while (analogRead(LeftRst) < TrigPoint)
  {
    leftTurn.run();
  }
  leftTurn.setCurrentPosition(0);
  //Serial.println("leftTurn Stopped!");

  rightTurn.move(FullTurn);
  while (analogRead(RightRst) < TrigPoint)
  {
    rightTurn.run();
  }
  rightTurn.setCurrentPosition(0);
  //Serial.println("rightTurn Stopped!");
#endif
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
  
  //Serial.println("initMotor Done!");
}

void TurnTolerance(AccelStepper motor, bool spin_direction) {
  if (spin_direction) {
    motor.move(tolerance);
    motor.runToPosition();
    
    motor.move(- calibration - tolerance);
    motor.runToPosition();
  }
  else {
    motor.move(-tolerance);
    motor.runToPosition();
    
    motor.move(calibration + tolerance);
    motor.runToPosition();
  }
}

// twelve different functions below executes the solving 
// sequence by turing the faces of cubes. the function
// also takes in account the next move to increase efficiency.
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
  
  TurnTolerance(frontTurn, true);
  
  frontSlide.move(-SlideDist);
  frontSlide.runToPosition();

  if (n != 2)
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
  
  TurnTolerance(frontTurn);

  frontSlide.move(-SlideDist);
  frontSlide.runToPosition();

  if (n != 2)
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

  if (n != 2)
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

  if (n != 2)
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

  if (n != 2)
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

  if (n != 2)
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

  if (n != 2)
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

  if(n != 2)
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
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);

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

  if(n != 2)
	frontTurn.move(n * TurnDist);
  frontTurn.runToPosition();

  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
}

void topAnticlockwise()
{
  int n = 0;

  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);

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

  if(n != 2)
	backTurn.move(n * TurnDist);
  backTurn.runToPosition();

  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
}

void bottomClockwise()
{
  int n = 0;

  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);

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

  if(n != 2)
	frontTurn.move(n * TurnDist);
  frontTurn.runToPosition();

  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
}

void bottomAnticlockwise()
{
  int n = 0;

  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);

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

  if(n != 2)
	backTurn.move(n * TurnDist);
  backTurn.runToPosition();

  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(FRONTSLIDE, BACKSLIDE, GoClockwise, SlideDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoAntiClockwise, SlideDist);
  TurnTwoMotors(LEFTTURN, RIGHTTURN, GoAntiClockwise, TurnDist);
  SlideTwoMotors(LEFTSLIDE, RIGHTSLIDE, GoClockwise, SlideDist);
}

// these two functions are made for convenience in programming the
// top two functions, which use these extensively.
void SlideTwoMotors(byte Motor1, byte Motor2, byte Direction, int nSteps)
{
  if (Motor1 == Motor2)
    return;

  if (Direction > GoAntiClockwise && Direction > GoClockwise)
    return;

  if (Direction == GoClockwise)
  {
    pmotor[Motor1]->move(nSteps);
    pmotor[Motor2]->move(nSteps);
  }
  else
  {
    pmotor[Motor1]->move(-nSteps);
    pmotor[Motor2]->move(-nSteps);
  }

  while (pmotor[Motor1]->distanceToGo() != 0 || pmotor[Motor2]->distanceToGo() != 0)
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

  while (pmotor[Motor1]->distanceToGo() != 0 || pmotor[Motor2]->distanceToGo() != 0)
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
