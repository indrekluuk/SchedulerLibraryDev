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
    static const uint8_t SEQUENCE_UNDEFINED = 0xFF;

    MethodCallback<Sequencer> m_sequenceNextCallback;
    Scheduler m_sequenceDelayScheduler;
    uint8_t m_sequenceIdentifier;
    uint8_t m_sequenceStep;
    bool m_hasNextStep;
    Callback* m_sequenceDoneCallback;

public:

    Sequencer();

    void start();
    void start(uint8_t sequenceIdentifier);
    void start(Callback* done);
    void start(uint8_t sequenceIdentifier, Callback* done);

    bool isRunning();
    bool isRunning(uint8_t sequenceIdentifier);

    void stop();

    void nextWithDelay(uint32_t time_ms);
    Callback& nextWhenDone();

protected:

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
    FunctionSequencer(NextStepFunction sequenceStepFunction) : m_sequenceStepFunction(sequenceStepFunction) {}

    FunctionSequencer& set(NextStepFunction sequenceStepFunction) {
        m_sequenceStepFunction = sequenceStepFunction;
        return *this;
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
    TObj* m_obj;
    SequenceStepMethod m_sequenceStepMethod;


public:
    MethodSequencer() :
            m_obj(NULL), m_sequenceStepMethod(NULL)
    {}

    MethodSequencer(TObj* obj) :
            m_obj(obj), m_sequenceStepMethod(NULL)
    {}

    MethodSequencer(TObj* obj, SequenceStepMethod sequenceStepMethod) :
            m_obj(obj), m_sequenceStepMethod(sequenceStepMethod)
    {}

    MethodSequencer& set(TObj* object) {
        m_obj = object;
        return *this;
    }

    MethodSequencer& set(SequenceStepMethod sequenceStepMethod) {
        m_sequenceStepMethod = sequenceStepMethod;
        return *this;
    }

protected:

    void callNextStep() { //override;
        if (m_obj != NULL && m_sequenceStepMethod != NULL) {
            (m_obj->*m_sequenceStepMethod)(*this, m_sequenceStep);
        }
    }

};





#endif


