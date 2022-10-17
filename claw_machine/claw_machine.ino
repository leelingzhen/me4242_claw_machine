#include <Servo.h>

#define SIGNAL_PIN 6
#define SERVO_PIN 9
#define BUTTON_PIN 3 

Servo servo_arm;

//servo settings
const int servo_step_delay = 10;
const int retract_angle = 100; //90 will be max, completely horizontal
const int extend_angle = 170;// 180 will be max, completely vertical
 

void setup() {
  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN, OUTPUT);

  //servo setup
  servo_arm.attach(SERVO_PIN);
  //init pos, retracted position
  servo_arm.write(retract_angle);
}

void loop() {
  // put your main code here, to run repeatedly:
  arm_extend(servo_arm);
  arm_retract(servo_arm);

}

void release_grip_at_home(int sequence_delay) {
  /*claw machine function when the player_button is depressed
  sequence of motion:

  1. arm will be extended
  2. soft actuator claw will close and grip object
  3. arm will retract 
  4. stepper motors will move in x then z direction
  5. soft claw will open and release object
  */
  arm_extend(servo_arm);
  delay(sequence_delay);
  claw_actuate(1);
  delay(sequence_delay);
  arm_retract(servo_arm);
  delay(sequence_delay);
  // code for stepper motors to move in X then Z direction to home

  // code ends here
  delay(sequence_delay);
  claw_actuate(0);
}


int player_button(){
  //returns 1 if the button has been pressed and zero if the button has been released
  int button_state = digitalRead(BUTTON_PIN);
  return button_state;
}

void arm_retract(Servo servo) {
  int servo_pos = extend_angle;
  for (int i = 0; i <= extend_angle- retract_angle; i++) {
    servo.write(servo_pos - i);
    delay(servo_step_delay);
  }
}

void arm_extend(Servo servo) {
  int servo_pos = retract_angle;
  for (int i = 0; i <=extend_angle - retract_angle; i++) {
    servo.write(servo_pos + i);
    delay(servo_step_delay);
  }
}

void claw_actuate(int signal) {
//to close or open the claw of the machine
  digitalWrite(SIGNAL_PIN, signal);
}
