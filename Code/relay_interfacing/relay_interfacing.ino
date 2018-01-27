// Physical no. of pin on board
int relay1 = 27;
int relay2 = 28;
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(relay1, OUTPUT);     
  pinMode(relay2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(relay1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(relay2, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  delay(2000);               // wait for a second
  digitalWrite(relay1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(relay2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(2000);               // wait for a second
}
