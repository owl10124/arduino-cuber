/*
 Name:		ArduinoMotorControl.ino
 Created:	6/8/2017 9:12:15 PM
 Author:	LINJING
*/

#include <AccelStepper.h>

#define POT1 A0

// Define a stepper and the pins it will use
AccelStepper stepper1(1, 3, 4);
AccelStepper stepper2(1, 5, 6);

int startTime = 0;

void setup()
{
	// Change these to suit your stepper if you want
	stepper1.setEnablePin(5);
	stepper1.setMaxSpeed(2000);
	stepper1.setAcceleration(2000);

	stepper2.setEnablePin(5);
	stepper2.setMaxSpeed(2000);
	stepper2.setAcceleration(2000);

	pinMode(POT1, INPUT);
}

void loop()
{
	// If at the end of travel go to the other end
	if (millis() - startTime >= analogRead(POT1))
		stepper1.move(1);

	stepper2.moveTo(analogRead(POT1));
	stepper2.run();
}
