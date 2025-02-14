/**
 *  Original Author: D S Brennan (github.com/dsbrennan)
 *  Created: 14/02/2025
 * 
 *  Display a morse code message on the internal LED:
 *  https://en.wikipedia.org/wiki/Morse_code
 *
 *  This code is based upon the standard arduino blink example:
 *  https://docs.arduino.cc/built-in-examples/basics/Blink/
 *
 *  Copyright 2025, MIT Licence
 **/

/*
  Morse code definitions:
  each dot ('.') is 1 time unit,
  each dash ('-') is 3 time units,
  a time unit is 1 second (1000 milliseconds)
*/
#define TIME_UNIT 1000
#define DOT_UNITS 1
#define DASH_UNITS 3

/*
  The morse code message to display,
  in this example the word DAN: D (-..) A (.-) N (-.)
*/
char output[7] = { '-', '.', '.', '.', '-', '-', '.' }; 
int current_char = 0;

void setup() {
  /*
    This method is run once, evertime your arduino is turned on.
    You should put any code in here that needs to have run before
    the 'loop' method.
  */

  // setup serial for diagnostics
  Serial.begin(9600);
  // clear the counter
  current_char = 0;
  // set the LED 'pin' to output
  pinMode(LED_BUILTIN, OUTPUT);
  // pause the system
  delay(3000);
  Serial.println("System Ready");
}

void loop() {
  /*
    This method is called on a loop untill your arduino is turned off.
    The main logic for your code should be present within this method.
  */

  // calculate amount of time LED is to be on for
  int led_on_time = 0;
  if(output[current_char] == '.'){
    Serial.println("Dot");
    led_on_time = DOT_UNITS * TIME_UNIT;
  } else if (output[current_char] == '-'){
    Serial.println("Dash");
    led_on_time = DASH_UNITS * TIME_UNIT;
  }

  // turn the LED on and off
  digitalWrite(LED_BUILTIN, HIGH);
  delay(led_on_time);
  digitalWrite(LED_BUILTIN, LOW);

  // determine the next sequence to display
  if (current_char > 7){
    current_char = 0;
  } else {
    current_char++;
  }

  // delay till next itteration
  delay(TIME_UNIT);
}
