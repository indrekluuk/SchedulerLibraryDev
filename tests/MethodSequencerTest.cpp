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





class MethodSequencerTest : public SchedulerTestBase {
protected:

    int methodCallbackCount;
    bool doneCallbackCalled;
    Callback* doSomethingElseCallback;

    virtual void SetUp() {
        methodCallbackCount = 0;
        doneCallbackCalled = false;
        doSomethingElseCallback = NULL;
    }

public:

    void simpleSequencerCallbackMethod(Sequencer &sequencer, uint8_t step) {
        methodCallbackCount++;

        switch (step) {
            case 1:
                sequencer.nextWithDelay(500);
                break;
            case 2:
                doSomethingElse(sequencer.nextWhenDone());
                break;
            case 3:
                sequencer.nextWithDelay(1000);
                break;
            case 4:
                break;
        }    }

    void sequencerDoneCallbackMethod() {
        doneCallbackCalled = true;
    }

    void doSomethingElse(Callback & callback) {
        doSomethingElseCallback = &callback;
    }


};



TEST_F(MethodSequencerTest, testCallbackSwitchFromFunctionToMethod) {
    MethodCallback<MethodSequencerTest> doneCallback(this, &MethodSequencerTest::sequencerDoneCallbackMethod);
    MethodSequencer<MethodSequencerTest> sequencer(this, &MethodSequencerTest::simpleSequencerCallbackMethod);

    ASSERT_EQ(0, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    sequencer.start(1, &doneCallback);

    ASSERT_EQ(1, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(495);
    ASSERT_EQ(1, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(10);
    ASSERT_EQ(2, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback != NULL);

    runScheduler(1000);
    ASSERT_EQ(2, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback != NULL);

    doSomethingElseCallback->call();
    doSomethingElseCallback = NULL;
    ASSERT_EQ(3, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(995);
    ASSERT_EQ(3, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(10);
    ASSERT_EQ(4, methodCallbackCount);
    ASSERT_TRUE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

};


