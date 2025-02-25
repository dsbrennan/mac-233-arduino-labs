/**
 *  Original Author: D S Brennan (github.com/dsbrennan)
 *  Created: 25/02/2025
 *
 *  Light up an LED when a hall effect sensor triggers
 *  an interrupt.
 *
 *  Copyright 2025, MIT Licence
 **/

/*
  Define pins used
  Nano every pinout diagram:
  https://docs.arduino.cc/resources/pinouts/ABX00028-full-pinout.pdf
*/
#define CRANK_PIN 2
#define CRANK_ACTIVITY_LED_PIN 4

/* 
  Define system constants
*/
#define CRANK_PASS_ACTIVITY_DELAY 500

/*
  System variables
 */
unsigned volatile long current_loop_time;
unsigned volatile long crank_interrupt_current_time;

void setup() {
  /*
    This method is run once, evertime your arduino is turned on.
    You should put any code in here that needs to have run before
    the 'loop' method.
  */

  // setup serial for diagnostics
  Serial.begin(9600);
  // set default values
  current_loop_time = 0;
  crank_interrupt_current_time = 0;
  // setup LED pin as output with LED off
  pinMode(CRANK_ACTIVITY_LED_PIN, OUTPUT);
  digitalWrite(CRANK_ACTIVITY_LED_PIN, LOW);
  // setup crank pin as input and attach an interrupt
  pinMode(CRANK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CRANK_PIN), crankInterrupt, FALLING);
  // pause the system
  delay(3000);
  Serial.println("System Ready");
}

void loop() {
  /*
    This method is called on a loop untill your arduino is turned off.
    The main logic for your code should be present within this method.
  */
  
  // display the crank activity LED
  current_loop_time = millis();
  if (current_loop_time - crank_interrupt_current_time < CRANK_PASS_ACTIVITY_DELAY) {
    digitalWrite(CRANK_ACTIVITY_LED_PIN, HIGH);
    Serial.println("Crank Active");
  } else {
    digitalWrite(CRANK_ACTIVITY_LED_PIN, LOW);
  }

  // delay the system
  delay(50);
}

void crankInterrupt() {
  /*
    This method is called everytime the hall effect sensor value is changed
    within the boundaries defined in setup.
  */

  // record the current time of interrupt in milliseconds
  crank_interrupt_current_time = millis();
}
