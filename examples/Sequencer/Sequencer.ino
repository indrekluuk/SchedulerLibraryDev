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




// class that does some work and calls "done" callback when it is finsihed
class SomeSubRutine {
private:
  MethodSequencer<SomeSubRutine> subroutineSequencer;
  
public:
  SomeSubRutine() : subroutineSequencer(this, &SomeSubRutine::subRoutineSequence) {}
  
  void doSomeWork(Callback* done) {
    subroutineSequencer.start(done);
  }
  
  void subRoutineSequence(Sequencer& sequencer, uint8_t step) {
    switch (step) {
      case 1:
        Serial.println("Sub-routine 1.");
        sequencer.nextWithDelay(1000);
        break;
      case 2:
        Serial.println("Sub-routine 2.");
        sequencer.nextWithDelay(1000);
        break;
      case 3:
        Serial.println("Sub-routine 3.");
        sequencer.nextWithDelay(1000);
        break;
      case 4:
        Serial.println("Sub-routine 4.");
        sequencer.nextWithDelay(1000);
        break;
      case 5:
        Serial.println("Sub-routine 5.");
        // if sequencer.next* is not called then this sequence finishes
        break;
    }
  }
  
};


// initialize class for sub-routine
SomeSubRutine subRouteine;
// function sequencer for main sequence
FunctionSequencer mainSequencer;




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
      // step 4 will be called when doSomeWork reparts that it has completed its task
      subRouteine.doSomeWork(&sequencer.nextWhenDone());
      break;
    case 4:
      Serial.println("Main sequence step 4. All done!");
      // if sequencer.next* is not called then this sequence finishes
      break;
  }
}






void setup() {
  Serial.begin(9600);
  // run main sequence when device starts
  mainSequencer.set(&mainSequence).start();
}



void loop() {
  // run scheduler timing checks
  Scheduler::run();
}

