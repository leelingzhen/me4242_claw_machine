// Include the AccelStepper Library
#include <AccelStepper.h>
// Adjust based on the steps movement
// Button must kill the joystick
// Define pin connections
// 2 inputs: step and direction
AccelStepper xStepper(1, 7, 6);
AccelStepper yStepper(2, 3, 4);
// Joystick Controls
const int VRx = A8;
const int VRy = A9;
const int SW = 5;

// Define motor interface type
#define motorInterfaceType 1
int xValue = 0;
int yValue = 0;
int swValue = 0;
int xMap = 0;
int yMap = 0;

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  xStepper.setMaxSpeed(600);
  xStepper.setSpeed(200);
  yStepper.setMaxSpeed(600);
  yStepper.setSpeed(200);
  Serial.begin(115200);
}

void loop() {
  xValue = analogRead(VRx);
  yValue = analogRead(VRy);
  // Serial.print(xValue);
  // Serial.print("\t");
  // Serial.print(yValue);
  // Serial.print("\t");
  xMap = map(xValue,0,1023,-3,3);
  yMap = map(yValue,0,1023,-3,3);
  if (xMap == 1 or xMap == -1) {
    xMap=0;
  }
  if (yMap == 1 or yMap == -1) {
    yMap=0;
  }
  // Move the motor one step
  xStepper.setSpeed(200*xMap);
  xStepper.runSpeed();
  yStepper.setSpeed(200*xMap);
  yStepper.runSpeed();
  Serial.print('2');
  Serial.print("\t");
}
