#include <Servo.h>

#define SIGNAL_PIN 6
#define RIGHT_SERVO 9
#define LEFT_SERVO 10

Servo right_servo;
Servo left_servo;

//servo settings
const int servo_step_delay = 10;
const int arm_up_angle = 100;
const int arm_down_angle = 170;
 

void setup() {
  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN, OUTPUT);

  //servo setup
  right_servo.attach(RIGHT_SERVO);
  left_servo.attach(LEFT_SERVO);
  //init pos, up position
  right_servo.write(arm_up_angle);
  left_servo.write(180 - arm_up_angle);
}

void loop() {
  // put your main code here, to run repeatedly:
  arm_up();
  arm_down();

}


void arm_up() {
	int right_servo_pos = arm_down_angle;
	int left_servo_pos = 180 - arm_down_angle;
	for (int i = 0; i <= arm_down_angle - arm_up_angle; i++) {
		right_servo.write(right_servo_pos - i);
		left_servo.write(left_servo_pos + i);
		delay(servo_step_delay);
	}
}

void arm_down() {
	int right_servo_pos = arm_up_angle;
	int left_servo_pos = 180 - arm_up_angle;
	for (int i = 0; i <= arm_down_angle - arm_up_angle; i++) {
		right_servo.write(right_servo_pos + i);
		left_servo.write(left_servo_pos -i);
		delay(servo_step_delay);
	}
}




void claw_actuate(int signal) {
//to close or open the claw of the machine
  digitalWrite(SIGNAL_PIN, signal);
}
