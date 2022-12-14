#include "Arduino.h"
#include <AccelStepper.h>
#include "StepperManager.h"

StepperManager::StepperManager(int xMotorInterface, int xMotorPin1, int xMotorPin2, int yMotorInterface, int yMotorPin1, int yMotorPin2, int joystickXPin, int joystickYPin, int joystickSwitchPin) 
: _xMotor(xMotorInterface, xMotorPin1, xMotorPin2), _yMotor(yMotorInterface, yMotorPin1, yMotorPin2), _joystickXPin(joystickXPin), _joystickYPin(joystickYPin), _joystickSwitchPin(joystickSwitchPin) {
}

void StepperManager::motorSetup(){
  StepperManager::motorSetup(600, 200);
}

void StepperManager::motorSetup(int maxSpeed, int currentSpeed){
  StepperManager::motorSetup(maxSpeed, currentSpeed, maxSpeed, currentSpeed);
}

void StepperManager::motorSetup(int maxSpeedX, int currentSpeedX, int maxSpeedY, int currentSpeedY){
  _xMotor.setMaxSpeed(maxSpeedX);
  _xMotor.setSpeed(currentSpeedX);
  _yMotor.setMaxSpeed(maxSpeedY);
  _yMotor.setSpeed(currentSpeedY);
}

int* StepperManager::readJoystick(){
  int xValue = analogRead(_joystickXPin);
  int yValue = analogRead(_joystickYPin);
  int xMap = map(xValue,0,1023,-3,3);
  int yMap = map(yValue,0,1023,-3,3);
  if (xMap == 1 or xMap == -1) {
    xMap=0;
  }
  if (yMap == 1 or yMap == -1) {
    yMap=0;
  }
  static int returnList[2];
  returnList[0] = xMap;
  returnList[1] = yMap;
  return returnList;
}

void StepperManager::moveMotor(int multiplierX, int multiplierY, bool shouldReadJoystick = true){
  if(shouldReadJoystick){
    int* joystickValues = readJoystick();
    _xMotor.setSpeed(multiplierX*joystickValues[0]);
    _xMotor.runSpeed();
    _yMotor.setSpeed(multiplierY*joystickValues[1]);
    // Serial.print(multiplierY*joystickValues[1]);
    _yMotor.runSpeed();
  } else{
    _xMotor.setSpeed(multiplierX);
    _xMotor.runSpeed();
    _yMotor.setSpeed(multiplierY);
    _yMotor.runSpeed();
  }
}

void StepperManager::moveMotor(int multiplier){
  moveMotor(multiplier, multiplier);
}