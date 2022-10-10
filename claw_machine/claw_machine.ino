
#define SIGNAL_PIN 6


void setup() {
  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SIGNAL_PIN, HIGH);
  delay(1000);
  digitalWrite(SIGNAL_PIN, LOW);
  delay(1000);
}



double [] joystick_output() {
/* function to get the joystick positions should return a double array of [x_mappings,y_mappings]
values taken from analog input should be divded by 1024
*/
}

void move_x(double gain) {
//moving claw machine in x direction with gain taken from joystick output
//should function consider killswitch?

}

void move_z(double gain) {
//same as move_x

}

void claw_actuate(int signal) {
//to close or open the claw of the machine
  digitalWrite(SIGNAL_PIN, signal)
}
