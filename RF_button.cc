#include <RCSwitch.h>
#include <avr/sleep.h>

/*
  https://github.com/sui77/rc-switch/
  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  https://playground.arduino.cc/Learning/ArduinoSleepCode/

*/

#define RF_PIN 10;
#define PULSE_LENGTH 320;
#define PROTOCOL 1;
#define REPEAT 2;
#define PIN_BUTTON 4;

int rf_pin = 10;            // data pin for rf comunication
int pulse_length = 320;     //
int protocol = 1;           // rf transmission protocol
int repeat = 15;            // repeat times while transmitting
int sensor_pin = 4;         //pin attached to button and to sensor
int led_pin = 6;            //pin with led for data transmission indication

int data_on = 5393;         //data to send
int data_off = 5396;        //data to send

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled !!! initial state 0 so that code rea
unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers!!!!!!!!!! milli sec

// **** SLEAPING VARS
int wake_pin = 2;                 // pin used for waking up, standart pin for interupt
int sleepStatus = 0;             // variable to store a request for sleep
int count = 0;                   // counter

RCSwitch mySwitch = RCSwitch();

void wakeUpNow()        // here the interrupt is handled after wakeup
{
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
}

void setup() {

  Serial.begin(9600);       //for serial debuging

  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(rf_pin);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set protocol (default is 1, will work for most outlets)
  // do not work with sonof rf bridge
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  // One repetition is barely notacable
  mySwitch.setRepeatTransmit(repeat);

  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(wake_pin, INPUT);
  pinMode(led_pin, OUTPUT);


  /* Now it is time to enable an interrupt. In the function call
     attachInterrupt(A, B, C)
     A   can be either 0 or 1 for interrupts on pin 2 or 3.

     B   Name of a function you want to execute while in interrupt A.

     C   Trigger mode of the interrupt pin. can be:
                 LOW        a low level trigger
                 CHANGE     a change in level trigger
                 RISING     a rising edge of a level trigger
                 FALLING    a falling edge of a level trigger

     In all but the IDLE sleep modes only LOW can be used.
  */

  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function wakeUpNow when pin 2 gets LOW

}

void sleepNow()         // here we put the arduino to sleep
{
  /* Now is the time to set the sleep mode. In the Atmega8 datasheet
     https://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
     there is a list of sleep modes which explains which clocks and
     wake up sources are available in which sleep mode.

     In the avr/sleep.h file, the call names of these sleep modes are to be found:

     The 5 different modes are:
         SLEEP_MODE_IDLE         -the least power savings
         SLEEP_MODE_ADC
         SLEEP_MODE_PWR_SAVE
         SLEEP_MODE_STANDBY
         SLEEP_MODE_PWR_DOWN     -the most power savings

     For now, we want as much power savings as possible, so we
     choose the according
     sleep mode: SLEEP_MODE_PWR_DOWN

  */
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here

  sleep_enable();          // enables the sleep bit in the mcucr register
  // so sleep is possible. just a safety pin

  /* Now it is time to enable an interrupt. We do it here so an
     accidentally pushed interrupt button doesn't interrupt
     our running program. if you want to be able to run
     interrupt code besides the sleep function, place it in
     setup() for example.

     In the function call attachInterrupt(A, B, C)
     A   can be either 0 or 1 for interrupts on pin 2 or 3.

     B   Name of a function you want to execute at interrupt for A.

     C   Trigger mode of the interrupt pin. can be:
                 LOW        a low level triggers
                 CHANGE     a change in level triggers
                 RISING     a rising edge of a level triggers
                 FALLING    a falling edge of a level triggers

     In all but the IDLE sleep modes only LOW can be used.
  */

  attachInterrupt(0, wakeUpNow, HIGH); // use interrupt 0 (pin 2) and run function
  // wakeUpNow when pin 2 gets LOW

  sleep_mode();            // here the device is actually put to sleep!!
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  sleep_disable();         // first thing after waking from sleep:
  // disable sleep...
  detachInterrupt(0);      // disables interrupt 0 on pin 2 so the
  // wakeUpNow code will not be executed
  // during normal running time.

}

void loop() {
  // display information about the counter
  delay(100);
  Serial.println("Awake");

  //int dataOn = 5393;
  //int dataOff = 5396;

  // Serial.println(analogRead(1));
  // Serial.println((millis() - lastDebounceTime));

  // read the state of the switch into a local variable:
  // digitalWrite(6, LOW);
  // if (digitalRead(4) == HIGH || analogRead(1) > 400 ) {

  //   //execute if time diference before last trip have more then debounceDelay
  //   if ((millis() - lastDebounceTime) > debounceDelay) {
  //     Serial.println("In sending function");
  //     digitalWrite(6, HIGH);
  //     mySwitch.send(data_on, 24);
  //     lastDebounceTime = millis();
  //   }

  // }

  mySwitch.send(data_on, 24);
  count++;
  delay(100);

  // sleepNow();




  // delay(1000);                           // waits for a second

  // compute the serial input
  // if (Serial.available()) {
  //   int val = Serial.read();
  //   if (val == 'S') {
  //     Serial.println("Serial: Entering Sleep mode");
  //     delay(100);     // this delay is needed, the sleep
  //     //function will provoke a Serial error otherwise!!
  //     count = 0;
  //     sleepNow();     // sleep function called here
  //   }
  //   if (val == 'A') {
  //     Serial.println("Hola Caracola"); // classic dummy message
  //   }
  // }
  
  // check if it should go to sleep because of time
  // if (count >= 1) {
    // Serial.println("Timer: Entering Sleep mode");
    Serial.print("Data: ");
    Serial.print(data_on);
    Serial.println(" sent");
    Serial.println("Goint to sleep");

    delay(100);     // this delay is needed, the sleep
    //function will provoke a Serial error otherwise!!
    count = 0;
    sleepNow();     // sleep function called here
  // }

}
