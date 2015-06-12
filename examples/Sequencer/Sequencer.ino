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

#include <Sequencer.h>




class SomeSubRutine {
private:
  MethodSequencer<SomeSubRutine> subroutineSequencer;
  
public:
  SomeSubRutine() : subroutineSequencer(this, &SomeSubRutine::subRoutineSequence) {}
  
  void doSomething(Callback* done) {
    subroutineSequencer.startSequence(1, done);
  }
  
  void subRoutineSequence(Sequencer& sequencer, uint8_t step) {
    switch (step) {
      case 1:
        Serial.println("Sub-routine 1.");
        sequencer.nextWithDelay(500);
        break;
      case 2:
        Serial.println("Sub-routine 2.");
        sequencer.nextWithDelay(500);
        break;
      case 3:
        Serial.println("Sub-routine 3.");
        sequencer.nextWithDelay(500);
        break;
      case 4:
        Serial.println("Sub-routine 4.");
        sequencer.nextWithDelay(500);
        break;
      case 5:
        Serial.println("Sub-routine 5.");
        break;
    }
  }
  
};



SomeSubRutine subRouteine;


void mainSequence(Sequencer& sequencer, uint8_t step) {
  switch (step) {
    case 1:
      Serial.println("Main sequence step 1. Waiting 3 seconds...");
      sequencer.nextWithDelay(3000);
      break;
    case 2:
      Serial.println("Main sequence step 2. Waiting another 5 seconds...");
      sequencer.nextWithDelay(5000);
      break;
    case 3:
      Serial.println("Main sequence step 3. Waiting for sub-routine to do its job...");
      subRouteine.doSomething(&sequencer.nextWhenDone());
      break;
    case 4:
      Serial.println("Main sequence step 4. All done!");
      break;
  }
}


static const uint8_t MAIN_SEQUENCE_IDENTIFIER = 1;
FunctionSequencer mainSequencer;



void setup() {
  Serial.begin(9600);
  mainSequencer.set(&mainSequence).startSequence(MAIN_SEQUENCE_IDENTIFIER);
}



void loop() {
  // run scheduler timing checks
  Scheduler::run();
}

