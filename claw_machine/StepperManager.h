/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef StepperManager_h

#define StepperManager_h

#include "Arduino.h"

class StepperManager {
  public:
        StepperManager(AccelStepper xMotor, AccelStepper yMotor, int joystickXPin, int joyStickYPin);
        StepperManager(int xMotorInterface, int xMotorPin1, int xMotorPin2, int yMotorInterface, int yMotorPin1, int yMotorPin2, int joystickXPin, int joyStickYPin, int joystickSwitchPin);
        int* readJoystick();
        void motorSetup();
        void motorSetup(int maxSpeed, int currentSpeed);
        void motorSetup(int maxSpeedX, int currentSpeedX, int maxSpeedY, int currentSpeedY);
        void moveMotor(int multiplierX, int multiplierY, bool shouldReadJoystick=true);
        void moveMotor(int multiplier);

  private:
    AccelStepper _xMotor;
    AccelStepper _yMotor;
    int _joystickXPin;
    int _joystickYPin;
    int _joystickSwitchPin;
};

#endif