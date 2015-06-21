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

#include "SchedulerTestBase.h"
#include "Sequencer.h"





class SequencerImmediateReturnTest : public SchedulerTestBase {

protected:

    MethodSequencer<SequencerImmediateReturnTest> m_mainSequencer;
    MethodSequencer<SequencerImmediateReturnTest> m_subSequencer;

    SequencerImmediateReturnTest() :
            m_mainSequencer(this),
            m_subSequencer(this)
    {}

public:


    void sequencerStep_immediateNextForever(Sequencer &sequencer, uint8_t step) {
        sequencer.nextWhenDone().call();
    }


    void sequencerStep_startSubSequence(Sequencer &sequencer, uint8_t step) {
        if (step == 1) {
            m_subSequencer.start(&sequencer.nextWhenDone());
        }
    }


    void sequencerStep_immediateReturn(Sequencer &sequencer, uint8_t step) {
    }


};


/*
TEST_F(SequencerImmediateReturnTest, testMainSequenceWithImmediateDone) {
    m_mainSequencer.set(&SequencerImmediateReturnTest::sequencerStep_immediateNextForever);
    m_mainSequencer.start();
}
*/


TEST_F(SequencerImmediateReturnTest, testSubSequenceWithImmediateDone) {
    m_mainSequencer.set(&SequencerImmediateReturnTest::sequencerStep_startSubSequence);
    m_subSequencer.set(&SequencerImmediateReturnTest::sequencerStep_immediateReturn);
    m_mainSequencer.start();
}



