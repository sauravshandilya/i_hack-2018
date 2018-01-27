/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// Physical no. of pin on board
int LED_RED = 29;
int LED_GREEN = 10;
int LED_YELLOW = 9;
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED_RED, OUTPUT);     
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED_RED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_GREEN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_YELLOW, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED_RED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_GREEN, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_YELLOW, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
}

