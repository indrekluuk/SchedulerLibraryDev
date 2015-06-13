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

#include "Sequencer.h"





Sequencer::Sequencer() :
        m_sequenceNextCallback(this, &Sequencer::initNextStep),
        m_sequenceDelayScheduler(&m_sequenceNextCallback),
        m_sequenceIdentifier(SEQUENCE_STOPPED),
        m_sequenceStep(0),
        m_hasNextStep(false),
        m_sequenceDoneCallback(NULL)
{
}



void Sequencer::start() {
    start(SEQUENCE_UNDEFINED, NULL);
}

void Sequencer::start(uint8_t sequenceIdentifier) {
    start(sequenceIdentifier, NULL);
}

void Sequencer::start(Callback* done) {
    start(SEQUENCE_UNDEFINED, done);
}

void Sequencer::start(uint8_t sequenceIdentifier, Callback* done) {
    m_sequenceIdentifier = sequenceIdentifier;
    m_sequenceStep = 0;
    m_sequenceDoneCallback = done;
    initNextStep();
}


bool Sequencer::isRunning() {
    return SEQUENCE_STOPPED != m_sequenceIdentifier;
}

bool Sequencer::isRunning(uint8_t sequenceIdentifier) {
    return sequenceIdentifier == m_sequenceIdentifier;
}


void Sequencer::stop() {
    m_sequenceIdentifier = SEQUENCE_STOPPED;
    m_sequenceStep = 0;
    m_sequenceDelayScheduler.stop();
}


void Sequencer::initNextStep() {
    m_sequenceStep++;
    m_hasNextStep = false;
    callNextStep();
    if (!m_hasNextStep) {
        sequenceDone();
    }
}



void Sequencer::nextWithDelay(uint32_t time_ms) {
    m_hasNextStep = true;
    m_sequenceDelayScheduler.runOnce(time_ms);
}



Callback&Sequencer::nextWhenDone() {
    m_hasNextStep = true;
    return m_sequenceNextCallback;
}



void Sequencer::sequenceDone() {
    stop();
    callDone();
}


void Sequencer::callDone() {
    if (m_sequenceDoneCallback != NULL) {
        m_sequenceDoneCallback->call();
    }
}

