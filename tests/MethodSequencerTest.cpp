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

    sequencer.startSequence(1, &doneCallback);

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


