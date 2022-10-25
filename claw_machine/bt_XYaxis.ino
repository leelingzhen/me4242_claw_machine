// Include the AccelStepper Library
#include <AccelStepper.h>
#include <Servo.h>

class StepperManager {
  public:
        StepperManager(AccelStepper xMotor, AccelStepper yMotor, int joystickXPin, int joyStickYPin);
        StepperManager(int xMotorInterface, int xMotorPin1, int xMotorPin2, int yMotorInterface, int yMotorPin1, int yMotorPin2, int joystickXPin, int joyStickYPin, int joystickSwitchPin);
        int* readJoystick();
        void motorSetup();
        void motorSetup(int maxSpeed, int currentSpeed);
        void motorSetup(int maxSpeedX, int currentSpeedX, int maxSpeedY, int currentSpeedY);
        void moveMotor(int multiplierX, int multiplierY);
        void moveMotor(int multiplier);

  private:
    AccelStepper _xMotor;
    AccelStepper _yMotor;
    int _joystickXPin;
    int _joystickYPin;
    int _joystickSwitchPin;
};

StepperManager::StepperManager(int xMotorInterface, int xMotorPin1, int xMotorPin2, int yMotorInterface, int yMotorPin1, int yMotorPin2, int joystickXPin, int joystickYPin, int joystickSwitchPin){
  _xMotor = AccelStepper(xMotorInterface, xMotorPin1, xMotorPin2);
  _yMotor = AccelStepper(yMotorInterface, yMotorPin1, yMotorPin2);
  _joystickXPin = joystickXPin;
  _joystickYPin = joystickYPin;
  _joystickSwitchPin = joystickSwitchPin;
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
  int returnList[] = {xMap, yMap};
  return returnList;
}

void StepperManager::moveMotor(int multiplierX, int multiplierY){
  int* joystickValues = readJoystick();
  _xMotor.setSpeed(multiplierX*joystickValues[0]);
  _xMotor.runSpeed();
  _yMotor.setSpeed(multiplierY*joystickValues[1]);
  _yMotor.runSpeed();
}

void StepperManager::moveMotor(int multiplier){
  moveMotor(multiplier, multiplier);
}

/** Stepper Code End **/

// Adjust based on the steps movement
// Button must kill the joystick
// Define pin connections
// 2 inputs: step and direction
StepperManager stepperMotors(1, 7, 6, 1, 3, 4, A8, A9, 5);

Servo servo_arm;
// Servo Controls
const int SIGNAL_PIN = 8;
const int SERVO_PIN = 9;
const int BUTTON_PIN = 10;
// Joystick Controls
const int VRx = A8;
const int VRy = A9;
const int SW = 5;

//servo settings
const int servo_step_delay = 10;
const int retract_angle = 100; //90 will be max, completely horizontal
const int extend_angle = 170;// 180 will be max, completely vertical


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

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  stepperMotors.motorSetup();  
  Serial.begin(115200);

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
  stepperMotors.moveMotor(200);
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


void claw_actuate(int signal) {
//to close or open the claw of the machine
  digitalWrite(SIGNAL_PIN, signal);
}



