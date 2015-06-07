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

#ifndef Callback_h
#define Callback_h

#include "SchedulerGlobals.h"


class Callback {
public:
    virtual void call() = 0;
};



class FunctionCallback : public Callback {

public:
    typedef void (*CallbackFunction)(void);

private:
    CallbackFunction m_callbackFunction;

public:
    FunctionCallback() :
            m_callbackFunction(NULL) {};

    FunctionCallback(CallbackFunction function) :
            m_callbackFunction(function) {};

    FunctionCallback& set(CallbackFunction function) {
        m_callbackFunction = function;
        return *this;
    }

    void call() {
        if (m_callbackFunction != NULL) {
            m_callbackFunction();
        }
    };
};




template<class TObj>
class MethodCallback : public Callback {

public:
    typedef void (TObj::*CallbackMethod)(void);

private:
    TObj* m_obj;
    CallbackMethod m_callbackMethod;

public:
    MethodCallback() :
            m_obj(NULL), m_callbackMethod(NULL) {};

    MethodCallback(TObj* object) :
            m_obj(object), m_callbackMethod(NULL) {};

    MethodCallback(TObj* object, CallbackMethod callbackMethod) :
            m_obj(object), m_callbackMethod(callbackMethod) {};


    MethodCallback& set(TObj* object) {
        m_obj = object;
        return *this;
    }

    MethodCallback& set(CallbackMethod callbackMethod) {
        m_callbackMethod = callbackMethod;
        return *this;
    }

    void call() {
        if (m_obj != NULL && m_callbackMethod != NULL) {
            (m_obj->*m_callbackMethod)();
        }
    };
};




#endif


