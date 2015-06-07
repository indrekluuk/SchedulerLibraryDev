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

#ifndef Scheduler_h
#define Scheduler_h

#include "Callback.h"
#include <Arduino.h>



class Scheduler {

private:
    static Scheduler *s_firstNode;
    Scheduler *m_nextNode;

    uint32_t m_timer_ms;
    uint32_t m_previousTime_ms;
    bool m_isRunOnce;


public:

    Scheduler();
    virtual ~Scheduler();

    static void run();

    void runPeriodically(uint32_t time_ms);
    void runOnce(uint32_t time_ms);
    void clearTimer();

private:

    void startTimer(uint32_t time_ms);

    void link();
    void unlink();
    static Scheduler *getNodeBefore(Scheduler *node);

    void checkTimer(uint32_t current_time_ms);
    bool isReady(const uint32_t &current_time_ms);
    virtual void call() = 0;
};





class CallbackScheduler : public Scheduler {

private:
    Callback* m_callback;

public:

    CallbackScheduler() :
            m_callback(NULL) {};

    CallbackScheduler(Callback* callback) :
            m_callback(callback) {};

    CallbackScheduler& set(Callback* callback) {
        m_callback = callback;
        return *this;
    }

protected:
    void call() { //override;
        if (m_callback != NULL) m_callback->call();
    }
};




class FunctionScheduler : public Scheduler {

public:
    typedef void (*CallbackFunction)(void);

private:
    FunctionCallback m_functionCallback;

public:

    FunctionScheduler() :
            m_functionCallback(NULL) {};

    FunctionScheduler(CallbackFunction function) :
            m_functionCallback(function) {};

    FunctionScheduler& set(CallbackFunction function) {
        m_functionCallback.set(function);
        return *this;
    }

protected:
    void call() { //override;
        m_functionCallback.call();
    }
};






template <class TObj>
class MethodScheduler : public Scheduler {

public:
    typedef void (TObj::*CallbackMethod)();

private:
    MethodCallback<TObj> m_methodCallback;

public:

    MethodScheduler() :
            m_methodCallback() {};

    MethodScheduler(TObj* callbackObj) :
            m_methodCallback(callbackObj) {};

    MethodScheduler(TObj* callbackObj, CallbackMethod method) :
            m_methodCallback(callbackObj, method) {};

    MethodScheduler& set(TObj* object) {
        m_methodCallback.set(object);
        return *this;
    }

    MethodScheduler& set(CallbackMethod method) {
        m_methodCallback.set(method);
        return *this;
    }

protected:
    void call() { //override;
        m_methodCallback.call();
    }
};




#endif


