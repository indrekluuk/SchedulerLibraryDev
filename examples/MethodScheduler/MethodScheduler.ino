#include <Scheduler.h>



class Led {
  
private:
  int m_ledPin;
  bool m_isOn;
  // every "Led" object will have its own private scheduler
  MethodScheduler<Led> m_scheduler;
  
public:
  // MethodScheduler must be initiated with the object whose methods are to be called
  Led(int ledPin) : m_ledPin(ledPin), m_isOn(false), m_scheduler(*this) {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  }
  
  // "MethodScheduler" calls object's method and therefore 
  // all object variables are accessible on callback
  void toggle() {
    m_isOn = !m_isOn;
    digitalWrite(m_ledPin, m_isOn?HIGH:LOW);
  }
  
  void startBlinking(unsigned long interval) {
    m_scheduler.callPeriodically(interval, &Led::toggle);
  }
};



Led led1(13);
Led led2(12);



void setup() {
  // Leds blink separatelly
  led1.startBlinking(500);
  led2.startBlinking(100);
}


void loop() {
  // run scheduler timing checks
  Scheduler::run();
}

