/*
  Example for different sending methods

  https://github.com/sui77/rc-switch/

*/

#define RF_PIN 10;
#define PULSE_LENGTH 320;
#define PROTOCOL 1;
#define REPEAT 2;
#define PIN_BUTTON 4;

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled !!! initial state 0 so that code rea
unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers!!!!!!!!!! milli sec

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);

  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set protocol (default is 1, will work for most outlets)
  // do not work with sonof rf bridge
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions. 
  //One repetition is barely notacable
  mySwitch.setRepeatTransmit(15);

  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, INPUT);
  pinMode(6, OUTPUT);

}

void loop() {
  
  int dataOn = 5393;
  int dataOff = 5396;
  
  Serial.println(analogRead(1));
  // Serial.println((millis() - lastDebounceTime));

  // read the state of the switch into a local variable:
  digitalWrite(6, LOW);
  if (digitalRead(4) == HIGH || analogRead(1) > 400 ) {

  //   //execute if time diference before last trip have more then debounceDelay
    if ((millis() - lastDebounceTime) > debounceDelay) {
      Serial.println("In sending function");
      digitalWrite(6, HIGH);
      mySwitch.send(dataOn, 24);
      lastDebounceTime = millis();
    }

  }
 

  // /* Same switch as above, but using decimal code */
  // mySwitch.send(dataOn, 24);
  // delay(1000);
  // mySwitch.send(dataOff, 24);
  // delay(1000);



  // /* Same switch as above, but using binary code */
  // mySwitch.send("000000000001010100010001");
  // delay(1000);
  // mySwitch.send("000000000001010100010100");
  // delay(1000);

}
