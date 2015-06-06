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

#ifndef Sequencer_h
#define Sequencer_h


#include "Scheduler.h"

class Sequencer {

public:

    static const uint8_t SEQUENCE_STOPPED = 0;

    MethodCallback<Sequencer> m_sequenceNextCallback;
    CallbackScheduler m_sequenceDelayScheduler;
    uint8_t m_sequenceIdentifier;
    uint8_t m_sequenceStep;
    bool m_hasNextStep;
    Callback* m_sequenceDoneCallback;

public:

    Sequencer();

    bool isSequenceRunning(uint8_t sequenceIdentifier);

    void stopSequence();

    void nextWithDelay(uint32_t time_ms);
    Callback& nextWhenDone();

protected:

    void initSequence(uint8_t sequenceIdentifier, Callback* done);
    virtual void callNextStep() = 0;

private:

    void initNextStep();
    void sequenceDone();
    void callDone();

};






class FunctionSequencer : public Sequencer {

public:
    typedef void (*NextStepFunction)(Sequencer & sequencer, uint8_t step);


private:
    NextStepFunction m_sequenceStepFunction;

public:
    FunctionSequencer() : m_sequenceStepFunction(NULL) {}

    void startSequence(uint8_t sequenceIdentifier, NextStepFunction sequenceStepFunction) {
        startSequence(sequenceIdentifier, NULL, sequenceStepFunction);
    }

    void startSequence(uint8_t sequenceIdentifier, Callback* done, NextStepFunction sequenceStepFunction) {
        m_sequenceStepFunction = sequenceStepFunction;
        initSequence(sequenceIdentifier, done);
    }

protected:

    void callNextStep() { //override;
        if (m_sequenceStepFunction != NULL) {
            m_sequenceStepFunction(*this, m_sequenceStep);
        }
    }

};






template<class TObj>
class MethodSequencer : public Sequencer {

public:
    typedef void (TObj::*SequenceStepMethod)(Sequencer & sequencer, uint8_t step);

private:
    TObj& m_obj;
    SequenceStepMethod m_sequenceStepMethod;


public:
    MethodSequencer(TObj& obj) :
            m_obj(obj), m_sequenceStepMethod(NULL)
    {}

    void startSequence(uint8_t sequenceIdentifier, SequenceStepMethod sequenceStepMethod) {
        startSequence(sequenceIdentifier, NULL, sequenceStepMethod);
    }

    void startSequence(uint8_t sequenceIdentifier, Callback* done, SequenceStepMethod sequenceStepMethod) {
        m_sequenceStepMethod = sequenceStepMethod;
        initSequence(sequenceIdentifier, done);
    }

protected:

    void callNextStep() { //override;
        if (m_sequenceStepMethod != NULL) {
            (m_obj.*m_sequenceStepMethod)(*this, m_sequenceStep);
        }
    }

};





#endif


