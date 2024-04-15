/*
 * Bluetooth Test - Arduino Side
 * Arduino to HM10 module to Google Chrome
 * https://www.amazon.com/gp/product/B06WGZB2N4/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
 * 
 * 
 * Example Link: https://www.youtube.com/watch?v=w_mRj5IlVpg
 * 
 * Twitter: https://twitter.com/KDcircuits
 * For inquiries or design services:
 * https://www.kdcircuits.com
 * 
 * License?  Do whatever you want with this code - it's just a sample
 */


#include <SoftwareSerial.h>
#include <Adafruit_MotorShield.h>

//Pins  ************************
//UART TO HM10 Module
const uint8_t bluRX_ardTXpin = 3;
const uint8_t bluTX_ardRXpin = 2;

//RGB LED
const uint8_t LED_Pin = 8;
// Push Button
const uint8_t pushButtonPin = 6;

SoftwareSerial bluetooth(bluTX_ardRXpin, bluRX_ardTXpin);

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(10000, 2);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(10000, 1);


//function prototypes
void checkBluetooth();

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  bluetooth.print("AT+NAMEPoojasArduino");//found this here: ftp://imall.iteadstudio.com/Modules/IM130614001_Serial_Port_BLE_Module_Master_Slave_HM-10/DS_IM130614001_Serial_Port_BLE_Module_Master_Slave_HM-10.pdf
  pinMode(pushButtonPin, INPUT_PULLUP);

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

void loop() {

  checkBluetooth();//if something is coming at us


  if (!digitalRead(pushButtonPin)) {//send out
    bluetooth.print("Push Button");
    while (!digitalRead(pushButtonPin)) {}
    delay(20);
    bluetooth.print(" ");
  }


}

void checkBluetooth() {
  char charBuffer[20];//most we would ever see
  if (bluetooth.available() > 0) {
    int numberOfBytesReceived = bluetooth.readBytesUntil('\n', charBuffer, 19);
    charBuffer[numberOfBytesReceived] = '\0';
        Serial.print("Received: ");
        Serial.println(charBuffer);

    if (strstr(charBuffer, "LED OFF") == &charBuffer[0]) {
      Serial.println("Turning LED OFF");
      analogWrite(LED_Pin, 0);
    } else if (strstr(charBuffer, "LED ON") == &charBuffer[0]) {
      analogWrite(LED_Pin, 255);
    } else if (strstr(charBuffer, "Drink1") == &charBuffer[0]) {

      Serial.println("Begin loop");
      myMotor1->step(300, FORWARD, SINGLE);
      delay(2000);
      myMotor1->step(300, BACKWARD, SINGLE);
      
    }

  }
}
