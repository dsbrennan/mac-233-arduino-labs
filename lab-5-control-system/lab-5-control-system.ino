/**
 *  Original Author: D S Brennan (github.com/dsbrennan)
 *  Created: 25/02/2025
 *
 *  Create the basics of a ebike control system:
 *  As long as a hall effect sensor on the crank of
 *  the bike is triggered every N seconds, then
 *  slowly power up the ESC (servo) up to its maximum
 *  output value. If the hall effect sensor trigger
 *  falls outside the N second window, then power down
 *  the ESC. An LED should be activated every time 
 *  the hall effect sensor is triggered to provide 
 *  a visual feedback to the operating user.
 *
 *  Copyright 2025, MIT Licence
 **/
#include <Servo.h>

/*
  Define pins used
  Nano every pinout diagram:
  https://docs.arduino.cc/resources/pinouts/ABX00028-full-pinout.pdf
*/
#define CRANK_ACTIVITY_LED_PIN 4
#define CRANK_PIN 2
#define ESC_PIN 9

/* 
  Define system constants
*/
#define CRANK_PASS_ACTIVITY_DELAY 500
#define CRANK_PASS_MAXIMUM_DELAY 1500
#define MESSAGE_MAXIMUM_INTERVAL 1000

/*
  ESC Variables
*/
const float esc_step_up = 0.5;
const float esc_step_down = 3.0;

/*
  System variables
 */
unsigned volatile long crank_interrupt_current_time;
unsigned long current_loop_time;
unsigned long message_previous_time;
float esc_power_output;
Servo esc;

void setup() {
  /*
    This method is run once, evertime your arduino is turned on.
    You should put any code in here that needs to have run before
    the 'loop' method.
  */

  // setup serial for diagnostics
  Serial.begin(9600);
  // set default values
  crank_interrupt_current_time = 0;
  current_loop_time = 0;  
  message_previous_time = 0;
  // setup LED pin as output with LED off
  pinMode(CRANK_ACTIVITY_LED_PIN, OUTPUT);
  digitalWrite(CRANK_ACTIVITY_LED_PIN, LOW);
  // setup crank pin as input and attach an interrupt
  pinMode(CRANK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CRANK_PIN), crankInterrupt, FALLING);
  // setup ESC (servo) as output
  pinMode(ESC_PIN, OUTPUT);
  esc.attach(ESC_PIN);
  esc.write(0);
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
  } else {
    digitalWrite(CRANK_ACTIVITY_LED_PIN, LOW);
  }

  // power up or down the ESC
  if (current_loop_time - crank_interrupt_current_time < CRANK_PASS_MAXIMUM_DELAY) {
    if (esc_power_output + esc_step_up <= 180) {
      esc_power_output += esc_step_up;
    } else {
      esc_power_output = 180;
    }
  } else {
    if (esc_power_output - esc_step_down >= 0) {
      esc_power_output -= esc_step_down;
    } else {
      esc_power_output = 0;
    }
  }
  esc.write((int)esc_power_output);

  // display debug message
  if (current_loop_time - message_previous_time >= MESSAGE_MAXIMUM_INTERVAL){
    message_previous_time = current_loop_time;
    Serial.print("ESC power output: ");
    Serial.println(esc_power_output);
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
