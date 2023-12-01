/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->  http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(10000, 2);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(10000, 1);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
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
    if (r != -1) { // got something
      if (isdigit(r)) {
        acquisitionStarted = true;
        Serial.read(); // remove the byte from the incoming stream
        result = 10 * result + (r - '0'); // do the math, might overflow.
      } else {
        if (acquisitionStarted) {
          receiving = false; // we are done
        } else {
          Serial.read(); // ignore that byte and remove it from the incoming stream
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

  /*Serial.println("Begin loop");
  myMotor1->step(100, FORWARD, DOUBLE);
  delay(200);
  myMotor1->step(100, BACKWARD, DOUBLE);
  myMotor2->step(950, FORWARD, DOUBLE);
  myMotor1->step(2400, FORWARD, DOUBLE);
  delay(4000);
  myMotor1->step(1600, BACKWARD, DOUBLE);
  delay(2000);*/



  // Serial.println("Double coil steps");
  // myMotor->step(100, FORWARD, DOUBLE);
  // myMotor->step(100, BACKWARD, DOUBLE);

  // Serial.println("Interleave coil steps");
  // myMotor->step(100, FORWARD, INTERLEAVE);
  // myMotor->step(100, BACKWARD, INTERLEAVE);

  // Serial.println("Microstep steps");
  // myMotor->step(50, FORWARD, MICROSTEP);
  // myMotor->step(50, BACKWARD, MICROSTEP);
}