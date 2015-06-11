/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Indrek Luuk (indrek.luuk@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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
Scheduler scheduler;
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

