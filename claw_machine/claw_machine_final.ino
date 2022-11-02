// Include the AccelStepper Library
#include <AccelStepper.h>
#include "StepperManager.h"
#include <Servo.h>

// Adjust based on the steps movement
// Button must kill the joystick
// Define pin connections
// 2 inputs: step and direction
StepperManager stepperMotors(1, 7, 6, 1, 2, 3, A8, A9, 5);

Servo servo_arm;
// Servo Controls
const int SERVO_PIN = 9;
const int BUTTON_PIN = 10;
// const int BUTTON_PIN = 5;

// To be reset when coin is input
bool buttonPressed = false;

int player_button(){
  //returns 1 if the button has been pressed and zero if the button has been released
  int button_state = digitalRead(BUTTON_PIN);
  return button_state;
}

void claw_move_height(Servo servo, int direction , int duration = 1000){
  servo.writeMicroseconds(direction);
  delay(duration);
}

void grab_item_flow(Servo servo){
  claw_move_height(servo_arm, 1000, 3000); // Move claw down
  claw_move_height(servo_arm, 1430, 3000); // Stop the claw
  digitalWrite(SIGNAL_PIN, 1); // gripper grab
  claw_move_height(servo_arm, 2000, 3000); // Move claw up
  stepperMotors.moveMotor(200, 0);
  delay(4000);
  stepperMotors.moveMotor(0, 200);
  delay(4000);
  digitalWrite(SIGNAL_PIN, 0); // griper release
  buttonPressed = true; // so that the sequence runs only once
}

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  stepperMotors.motorSetup();
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN, OUTPUT);

  // Read the coin input pin -> use this to reset buttonPressed to false
  // Coin Input CODE HERE:

  // Coin Input CODE END
  //servo setup
  servo_arm.attach(SERVO_PIN);
  // servo_arm.write(86);
  servo_arm.writeMicroseconds(1430); // stop the servo upon initialization
}

void loop() {
  // put your main code here, to run repeatedly:
  stepperMotors.moveMotor(200);
  // if coin input is detected: UNCOMMENT
  // buttonPressed = false;
  if(!buttonPressed && player_button()){
    grab_item_flow();
  }
}
