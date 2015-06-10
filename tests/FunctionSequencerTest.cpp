#include "SchedulerTestBase.h"
#include "Sequencer.h"





class FunctionSequencerTest : public SchedulerTestBase {
protected:

    static int functionCallbackCount;
    static bool doneCallbackCalled;
    static Callback* doSomethingElseCallback;

    virtual void SetUp() {
        functionCallbackCount = 0;
        doneCallbackCalled = false;
        doSomethingElseCallback = NULL;
    }

    static void sequencerCallbackFunction(Sequencer &sequencer, uint8_t step) {
        functionCallbackCount++;

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
        }
    }



    static void sequencerDoneCallbackFunction() {
        doneCallbackCalled = true;
    }

    static void doSomethingElse(Callback & callback) {
        doSomethingElseCallback = &callback;
    }




};


int FunctionSequencerTest::functionCallbackCount = 0;
bool FunctionSequencerTest::doneCallbackCalled = false;
Callback * FunctionSequencerTest::doSomethingElseCallback = NULL;



TEST_F(FunctionSequencerTest, testCallbackSwitchFromFunctionToMethod) {
    FunctionCallback doneCallback(&FunctionSequencerTest::sequencerDoneCallbackFunction);
    FunctionSequencer sequencer(&FunctionSequencerTest::sequencerCallbackFunction);

    ASSERT_EQ(0, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    sequencer.startSequence(1, &doneCallback);

    ASSERT_EQ(1, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(495);
    ASSERT_EQ(1, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(10);
    ASSERT_EQ(2, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback != NULL);

    runScheduler(1000);
    ASSERT_EQ(2, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback != NULL);

    doSomethingElseCallback->call();
    doSomethingElseCallback = NULL;
    ASSERT_EQ(3, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(995);
    ASSERT_EQ(3, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

    runScheduler(10);
    ASSERT_EQ(4, functionCallbackCount);
    ASSERT_TRUE(doneCallbackCalled);
    ASSERT_TRUE(doSomethingElseCallback == NULL);

};


