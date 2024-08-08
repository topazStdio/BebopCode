

#include <PS4Controller.h>
#include <ESP32Servo.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "EyesAnimation.h"
#include "RobotMovement.h"

// variables for the displays
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 2

#define DATA_PIN  25
#define CS_PIN    26
#define CLK_PIN   27

// create a new instance of the class MD_MAX72XX
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Time delay beetwen frame
unsigned long delaytime = 200;
 

Servo servo1;
Servo servo2;

int mappedDataservo1 = 0;
int mappedDataservo2 = 0;

 
void setup() {
 
  // Setup Serial Monitor for testing
  Serial.begin(115200);

  // create pwm output for the servos
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo1.setPeriodHertz(50);    // standard 50 hz servo
	servo1.attach(33, 1000, 2000); // attaches the servo on pin 33 to the servo object
	servo2.setPeriodHertz(50);    // standard 50 hz servo
	servo2.attach(32, 1000, 2000); // attaches the servo on pin 32 to the servo object

 
  //start ps4 controller
  PS4.begin();
 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
  Serial.println("Ready.");

  //start the displays
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 8);
  mx.clear();
}

// function to turn 8bit pattern into rows and columns for the display
void displayPattern(byte *pattern) {
  for (int row = 0; row < 8; row++) {
    mx.setRow(0, row, pattern[row]);
    mx.setRow(1, row, pattern[row]);
  }
}

 
void loop() {

  //check if ps4 controller is connected
  if (PS4.isConnected()) {
    //move the motors according to the joystick movements
   if(PS4.LStickX() > 80) {
    right();
   } else if (PS4.LStickX() < -80){
    left();
   } else if (PS4.LStickY() < -80) {
    backward();
   } else if (PS4.LStickY() > 80) {
    forward();
   } else {
    stopMotors();
   }
   // move the servos according to the right joystick data
   mappedDataservo1 = map(PS4.RStickY(), -127, 