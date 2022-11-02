// Include the AccelStepper Library
#include <AccelStepper.h>
#include "StepperManager.h"
#include <Servo.h>

// As of 1st November: 1430microseconds or 86 is stop for servo
void arm_retract(Servo servo, int extend_angle, int retract_angle, int servo_step_delay) {
  int servo_pos = extend_angle;
  for (int i = 0; i <= extend_angle - retract_angle; i++) {
    servo.write(servo_pos - i);
    delay(servo_step_delay);
  }
}



// Adjust based on the steps movement
// Button must kill the joystick
// Define pin connections
// 2 inputs: step and direction
StepperManager stepperMotors(1, 7, 6, 1, 2, 3, A8, A9, 5);

Servo servo_arm;
// Servo Controls
const int SIGNAL_PIN = 8;
const int SERVO_PIN = 9;
// const int BUTTON_PIN = 10;
const int BUTTON_PIN = 5;

// To be reset when coin is input
bool buttonPressed = false;

int player_button(){
  //returns 1 if the button has been pressed and zero if the button has been released
  int button_state = digitalRead(BUTTON_PIN);
  return button_state;
}


void claw_actuate(int signal) {
//to close or open the claw of the machine
//send a signal of HIGH to close the claw and a signal of LOW to release the claww
  digitalWrite(SIGNAL_PIN, signal);
}

void claw_move_height(Servo servo, int direction , int duration = 1000, int stop = 1430){
  servo.writeMicroseconds(direction);
  Serial.println(direction);
  delay(1000);
  Serial.println("delay");
  servo.writeMicroseconds(stop);
  Serial.println("stop");
  delay(1000);
  servo.writeMicroseconds(2000);
  Serial.println(2000);
  delay(1000);
  Serial.println("delay");
  servo.writeMicroseconds(stop);
}

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  stepperMotors.motorSetup();  
  Serial.begin(115200);

  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN, OUTPUT);

  //servo setup
  servo_arm.attach(SERVO_PIN);
  // servo_arm.write(86);
  // servo_arm.writeMicroseconds(1430);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepperMotors.moveMotor(200);
  if(!buttonPressed && player_button()){
    claw_move_height(servo_arm, 1000);
    buttonPressed = true;
  }
}



// void release_grip_at_home(int sequence_delay) {
//   /*claw machine function when the player_button is depressed
//   sequence of motion:
//   1. arm will be extended
//   2. soft actuator claw will close and grip object
//   3. arm will retract 
//   4. stepper motors will move in x then z direction
//   5. soft claw will open and release object
//   */
//   arm_extend(servo_arm);
//   delay(sequence_delay);
//   claw_actuate(1);
//   delay(sequence_delay);
//   arm_retract(servo_arm);
//   delay(sequence_delay);
//   // code for stepper motors to move in X then Z direction to home

//   // code ends here
//   delay(sequence_delay);
//   claw_actuate(0);
// }

