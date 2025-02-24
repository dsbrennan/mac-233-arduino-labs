/**
 *  Original Author: D S Brennan (github.com/dsbrennan)
 *  Created: 20/02/2025
 *
 *  Rotate an external servo in a loop
 *
 *  Copyright 2025, MIT Licence
 **/
#include <Servo.h>

/*
  Define pins used
  Nano every pinout diagram:
  https://docs.arduino.cc/resources/pinouts/ABX00028-full-pinout.pdf
*/
#define SERVO_PIN 9

/*
  Create an instance of the Arduino Servo Library:
  https://docs.arduino.cc/libraries/servo/
*/
Servo servo;

/*
  The list of degrees to cycle through for the servo
*/
int output[7] = { 0, 30, 60, 90, 120, 150, 180 };
int output_position = 0;

void setup() {
  /*
    This method is run once, evertime your arduino is turned on.
    You should put any code in here that needs to have run before
    the 'loop' method.
  */

  // setup serial for diagnostics
  Serial.begin(9600);
  // reset the position
  output_position = 0;
  // set the servo pin to output
  pinMode(SERVO_PIN, OUTPUT);
  // attach the servo pin to the servo library
  servo.attach(SERVO_PIN);
  // set the servo to zero degrees
  servo.write(0);
  // pause the system
  delay(3000);
  Serial.println("System Ready");
}

void loop() {
  /*
    This method is called on a loop untill your arduino is turned off.
    The main logic for your code should be present within this method.
  */

  // move the servo to the correct position
  servo.write(output[output_position]);
  Serial.println(output[output_position]);

  // determine next position
  if (output_position >= 6) {
    output_position = 0;
  } else {
    output_position++;
  }

  // wait 2 seconds untill the next itteration
  delay(2000);
}
