#include <Scheduler.h>

class Led {
  
  
  
private:
  int m_ledPin;
  bool m_isOn;
  
public:
  Led(int ledPin) : m_ledPin(ledPin), m_isOn(false) {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  }
  
  void on() {
    m_isOn = true;
    digitalWrite(m_ledPin, HIGH);
  }
  
  void toggle() {
    m_isOn = !m_isOn;
    digitalWrite(m_ledPin, m_isOn?HIGH:LOW);
  }  
};


// init led on pin 13
Led led(13);


// Scheduler object that accepts "Callback*" as callback parameter
CallbackScheduler scheduler;
// Callback for static functions (subclass of Callback)
FunctionCallback initBlinkingCallback(initBlinking);
// Callback for object methods (templated subclass of Callback)
MethodCallback<Led> blinkCallback(&led, &Led::toggle);




void setup() {
  // turn led on
  led.on();
  // call static function "initBlinking" after 5 seconds
  scheduler.set(&initBlinkingCallback).runOnce(5000);
}


void initBlinking() {
  // call periodically method "toggle" of object "led";
  scheduler.set(&blinkCallback).runPeriodically(500);
}



void loop() {
  // run scheduler timing checks
  Scheduler::run();
}

