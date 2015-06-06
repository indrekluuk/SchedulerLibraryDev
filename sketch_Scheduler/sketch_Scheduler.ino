
#include "scheduler.h"


const int ledPin = 13;


FunctionScheduler scheduler;



int ledState = LOW;

void toggleLed() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  scheduler.callPeriodically(1000, toggleLed);
}



void loop() {
  Scheduler::run();
}



