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



class TimedSerialOutput {
  
private:

  char* m_outputPrefix;
  int m_interval;
  // every object instance will have its own private scheduler
  MethodScheduler<TimedSerialOutput> m_scheduler;
  
public:
  
  TimedSerialOutput(char* prefix) : 
        m_outputPrefix(prefix), 
        m_interval(0), 
        // Init MethodScheduler with object whose methods are to be called
        m_scheduler(this) 
  {}
  
  // "MethodScheduler" calls object's method and therefore 
  // all object variables are accessible on callback
  void doOutput() {
    Serial.print(m_outputPrefix);
    Serial.print(m_interval);
    Serial.println(" millisecond tick");
  }
  
  void startOutput(unsigned long interval) {
    m_interval = interval;
    m_scheduler.set(&TimedSerialOutput::doOutput).runPeriodically(interval);
  }
};



TimedSerialOutput serial1("object 1: ");
TimedSerialOutput serial2("object 2: ");



void setup() {
  Serial.begin(9600);
  // objects operate separately with their own intervals
  serial1.startOutput(2000);
  serial2.startOutput(500);
}


void loop() {
  // run scheduler timing checks
  Scheduler::run();
}

