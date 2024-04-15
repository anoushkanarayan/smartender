#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(10000, 2);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(10000, 1);


void setup() {
  Serial.begin(9600);           
  while (!Serial);
  Serial.println("Stepper test!");

  if (!AFMS.begin()) {         
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  myMotor1->setSpeed(10);
  myMotor2->setSpeed(20);  // 10 rpm
}

unsigned long getUserInputBlocking(const char * message) {
  unsigned long result = 0;
  bool receiving = true;
  bool acquisitionStarted = false;
  Serial.println(message);
  do {
    int r = Serial.peek();
    if (r != -1) { 
      if (isdigit(r)) {
        acquisitionStarted = true;
        Serial.read(); 
        result = 10 * result + (r - '0'); 
      } else {
        if (acquisitionStarted) {
          receiving = false;
        } else {
          Serial.read(); 
        }
      }
    }
  } while (receiving);
  return result;
}

void loop() {

  int numSteps = getUserInputBlocking("type please");
  Serial.println("Begin loop");
  myMotor1->step(100, FORWARD, SINGLE);
  delay(200);
  myMotor1->step(100, BACKWARD, SINGLE);
  myMotor2->step(900, FORWARD, SINGLE);
  myMotor1->step(1400, FORWARD, DOUBLE);
  delay(1000);
  myMotor1->step(520, BACKWARD, DOUBLE);
  delay(2000);
  myMotor2->step(2300, FORWARD, SINGLE);
  myMotor1->step(1400, FORWARD, DOUBLE);
  delay(1000);
  myMotor1->step(600, BACKWARD, DOUBLE);
  delay(2000);
  myMotor2->step(3200, BACKWARD, SINGLE);
  delay(2000);

}