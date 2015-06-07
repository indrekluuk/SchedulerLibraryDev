#include "Arduino.h"


int milliseconds = 0;


void pinMode(int ledPin, int mode) {
}


void digitalWrite(int ledPin, int val) {
}


unsigned long millis() {
    return milliseconds;
}


void arduino_increase_millis(unsigned long time_ms) {
    milliseconds += time_ms;
}
