#include <Scheduler.h>


int ledPin = 13;
boolean isOn = false;


// Scheduler that accepts static function pointer as callback parameter
FunctionScheduler scheduler;

void toggleLed() {
  isOn = !isOn;
  digitalWrite(ledPin, isOn?HIGH:LOW);
  
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // call function "toggleLed" every 500 milliseconds  
  scheduler.set(toggleLed).runPeriodically(500);
}


void loop() {
  // run scheduler timing checks
  Scheduler::run();
}
