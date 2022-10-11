// Include the AccelStepper Library
#include <AccelStepper.h>

// Define pin connections
AccelStepper myStepper(1, 7, 6);
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
  myStepper.setMaxSpeed(600);
  // myStepper.setAcceleration(50);
  myStepper.setSpeed(200);
  Serial.begin(115200);
}

void loop() {
  xValue = analogRead(VRx);
  yValue = analogRead(VRy);
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\t");
  xMap = map(xValue,0,1023,-3,3);
  yMap = map(yValue,0,1023,-3,3);
  if (xMap == 1 or xMap == -1) {
    xMap=0;
  }
  // Move the motor one step
  myStepper.setSpeed(200*xMap);
  myStepper.runSpeed();
  Serial.print('2');
  Serial.print("\t");
}
