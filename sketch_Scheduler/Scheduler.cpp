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

#include "Scheduler.h"


Scheduler *Scheduler::s_firstNode = NULL;


Scheduler::Scheduler() :
        m_nextNode(NULL),
        m_timer_ms(0),
        m_previousTime_ms(0),
        m_isRunOnce(true),
        m_callback(NULL)
{
    link();
}

Scheduler::Scheduler(Callback * callback) :
        m_nextNode(NULL),
        m_timer_ms(0),
        m_previousTime_ms(0),
        m_isRunOnce(true),
        m_callback(callback)
{
    link();
}

Scheduler::~Scheduler() {
    unlink();
}

void Scheduler::link() {
    if (s_firstNode == NULL) {
        s_firstNode = this;
    } else {
        getNodeBefore(NULL)->m_nextNode = this;
    }
}

void Scheduler::unlink() {
    if (s_firstNode == this) {
        s_firstNode = m_nextNode;
    } else {
        getNodeBefore(this)->m_nextNode = m_nextNode;
    }
}

Scheduler *Scheduler::getNodeBefore(Scheduler *node) {
    if ((s_firstNode == NULL) || (s_firstNode == node)) return NULL;

    Scheduler* before = s_firstNode;
    while (before->m_nextNode != node) {
        before = before->m_nextNode;
    }
    return before;
}


void Scheduler::run() {
    uint32_t current_time_ms = millis();

    Scheduler *node = s_firstNode;
    while (node != NULL) {
        node->checkTimer(current_time_ms);
        node = node->m_nextNode;
    }
}

void Scheduler::checkTimer(uint32_t current_time_ms) {
    if (isReady(current_time_ms)) {
        if (m_isRunOnce) {
            stop();
        }
        call();
    }
}

bool Scheduler::isReady(const uint32_t &current_time_ms) {
    if (m_timer_ms == 0) return false;

    uint32_t elapsed_time_ms = current_time_ms - m_previousTime_ms;
    if (elapsed_time_ms >= m_timer_ms) {
        m_previousTime_ms = m_previousTime_ms + m_timer_ms;
        return true;
    } else {
        return false;
    }
}

void Scheduler::call() {
    if (m_callback != NULL) m_callback->call();
}



int Scheduler::getCount() {
    int count = 0;
    Scheduler *node = s_firstNode;
    while (node != NULL) {
        count++;
        node = node->m_nextNode;
    }
    return count;
}


Scheduler& Scheduler::set(Callback* callback) {
    m_callback = callback;
    return *this;
}

void Scheduler::runPeriodically(uint32_t time_ms) {
    m_isRunOnce = false;
    startTimer(time_ms);
}

void Scheduler::runOnce(uint32_t time_ms) {
    m_isRunOnce = true;
    startTimer(time_ms);
}

void Scheduler::startTimer(uint32_t time_ms) {
    m_timer_ms = time_ms;
    m_previousTime_ms = millis();
}

void Scheduler::stop() {
    m_timer_ms = 0;
}









