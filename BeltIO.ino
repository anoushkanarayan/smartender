/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->  http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *motor1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *motor2 = AFMS.getStepper(200, 2);

int myArray[2]; // Assuming you know the size of the array.
int arrayIndex = 0;
String inputString = ""; // Store the received string.

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  //if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  motor1->setSpeed(2000);  // 10 rpm
  // motor2->setSpeed(10);  // 10 rpm
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
  int numSteps = getUserInputBlocking("How many steps do you want to move?");
  Serial.println (numSteps);

  int directionChoice = getUserInputBlocking("Which direction do you want to move? 1: Forward; 2: Backward");
  Serial.println (directionChoice);

  if(directionChoice == 1) {
    motor1->step(numSteps, FORWARD, DOUBLE);
  } 
  if(directionChoice == 2) {
    motor1->step(numSteps, BACKWARD, DOUBLE);
  }
//  myArray[0] = 0;
//  myArray[1] = 0;
//  motor1->step(100, FORWARD, SINGLE);
//  motor1->step(100, BACKWARD, SINGLE);

//  motor2->step(100, FORWARD, SINGLE);
//  motor2->step(100, BACKWARD, SINGLE);

//  Serial.println("Double coil steps");
//  myMotor->step(100, FORWARD, DOUBLE);
//  myMotor->step(100, BACKWARD, DOUBLE);
//
//  Serial.println("Interleave coil steps");
//  myMotor->step(100, FORWARD, INTERLEAVE);
//  myMotor->step(100, BACKWARD, INTERLEAVE);
//
//  Serial.println("Microstep steps");
//  myMotor->step(50, FORWARD, MICROSTEP);
//  myMotor->step(50, BACKWARD, MICROSTEP);
}
