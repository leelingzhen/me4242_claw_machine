
//Pin Assigement 
#define VALVE_CTRL_0  3
#define VALVE_CTRL_1  9
#define VALVE_CTRL_2  10
#define VALVE_CTRL_3  11
#define PUMP_CTRL     5
#define PRESSURE_0    A0
#define PRESSURE_1    A1
#define PRESSURE_2    A2
#define PRESSURE_3    A3
#define SIGNAL_PIN 6

//define pump ON/OFF control
#define PUMP_ON   digitalWrite(PUMP_CTRL, HIGH);
#define PUMP_OFF  digitalWrite(PUMP_CTRL, LOW); 

//User Variables
int PRESSURE[4] ={0};
int pump_signal = 1;
int claw_toggle = 0;

void setup() {
  Serial.begin(115200);
  pinMode(VALVE_CTRL_0, OUTPUT);
  pinMode(VALVE_CTRL_1, OUTPUT);
  pinMode(VALVE_CTRL_2, OUTPUT);
  pinMode(VALVE_CTRL_3, OUTPUT);
  pinMode(PUMP_CTRL, OUTPUT);
  VALVE_OFF(VALVE_CTRL_0);
  VALVE_OFF(VALVE_CTRL_1);
  VALVE_OFF(VALVE_CTRL_2);
  VALVE_OFF(VALVE_CTRL_3);
  PUMP_OFF;

  //signal pin to be communicated by other arduino
  pinMode(SIGNAL_PIN,INPUT);
}

void loop() {
  pump_signal = digitalRead(SIGNAL_PIN);

  if (pump_signal == 1 && claw_toggle == 0){
    CLAW_GRIP();
    claw_toggle = 1;
    }
  if (pump_signal == 0){
    CLAW_RELEASE();
    claw_toggle = 0;
}

  
  
}

void CLAW_GRIP() {
  Serial.println("claw grip");
  PUMP_ON;
  //this part of the code may not be needed 
  //VALVE_ON(VALVE_CTRL_0);
  //delay(1000);
  //until here
  VALVE_OFF(VALVE_CTRL_0);
  delay(600);
  PUMP_OFF;
}

void CLAW_RELEASE() {
  Serial.println("claw_release");
  VALVE_ON(VALVE_CTRL_0);
  delay(1000);
}

void VALVE_ON(byte VALVE_INDEX){
  digitalWrite(VALVE_INDEX, HIGH);
}
void VALVE_OFF(byte VALVE_INDEX){
  digitalWrite(VALVE_INDEX, LOW);
}
void READ_PRESSURE(){
  PRESSURE[0]=analogRead(PRESSURE_0);
  PRESSURE[1]=analogRead(PRESSURE_1);
  PRESSURE[2]=analogRead(PRESSURE_2);
  PRESSURE[3]=analogRead(PRESSURE_3);
}
