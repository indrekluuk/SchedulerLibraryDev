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



class SchedulerTest : public SchedulerTestBase {
protected:

    static int functionCallbackCount;
    int methodCallbackCount;

    virtual void SetUp() {
        functionCallbackCount = 0;
        methodCallbackCount = 0;
    }

    static void schedulerCallbackFunction() {
        functionCallbackCount++;
    }


public:
    void schedulerCallbackMethod() {
        methodCallbackCount++;
    }

};

int SchedulerTest::functionCallbackCount = 0;



TEST_F(SchedulerTest, testCallbackSwitchFromFunctionToMethod) {
    FunctionCallback functionCallback(&SchedulerTest::schedulerCallbackFunction);
    MethodCallback<SchedulerTest> methodCallback(this, &SchedulerTest::schedulerCallbackMethod);

    Scheduler scheduler;

    scheduler.runPeriodically(500);

    runScheduler(510);
    ASSERT_EQ(0, functionCallbackCount);
    ASSERT_EQ(0, methodCallbackCount);

    scheduler.set(&functionCallback);
    runScheduler(500);
    ASSERT_EQ(1, functionCallbackCount);
    ASSERT_EQ(0, methodCallbackCount);

    scheduler.set(&methodCallback);
    runScheduler(500);
    ASSERT_EQ(1, functionCallbackCount);
    ASSERT_EQ(1, methodCallbackCount);
};


