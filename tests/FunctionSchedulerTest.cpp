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






class FunctionSchedulerTest : public SchedulerTestBase {
protected:

    static int callbackCount;

    virtual void SetUp() {
        callbackCount = 0;
    }

    static void schedulerCallbackFunction() {
        callbackCount++;
    }

};

int FunctionSchedulerTest::callbackCount = 0;



TEST_F(FunctionSchedulerTest, testCallOnceCallback) {

    FunctionScheduler scheduler(FunctionSchedulerTest::schedulerCallbackFunction);

    scheduler.runOnce(500);
    runScheduler(495);
    ASSERT_EQ(0, callbackCount);
    runScheduler(10);
    ASSERT_EQ(1, callbackCount);
    runScheduler(500);
    ASSERT_EQ(1, callbackCount);
};



TEST_F(FunctionSchedulerTest, testPeriodicalCallback) {

    FunctionScheduler scheduler(FunctionSchedulerTest::schedulerCallbackFunction);

    scheduler.runPeriodically(500);
    runScheduler(495);
    ASSERT_EQ(0, callbackCount);
    runScheduler(10);
    ASSERT_EQ(1, callbackCount);
    runScheduler(500);
    ASSERT_EQ(2, callbackCount);
    runScheduler(500);
    ASSERT_EQ(3, callbackCount);
};




TEST_F(FunctionSchedulerTest, testInitFunctionLater) {

    FunctionScheduler scheduler;

    scheduler.runOnce(500);
    runScheduler(510);
    ASSERT_EQ(0, callbackCount);

    scheduler.set(FunctionSchedulerTest::schedulerCallbackFunction).runPeriodically(500);
    runScheduler(510);
    ASSERT_EQ(1, callbackCount);
    runScheduler(500);
    ASSERT_EQ(2, callbackCount);
};

