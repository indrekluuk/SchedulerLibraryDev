#include "SchedulerTestBase.h"
#include "Sequencer.h"





class FunctionSequencerTest : public SchedulerTestBase {
protected:

    static int functionCallbackCount;
    static bool doneCallbackCalled;

    virtual void SetUp() {
        functionCallbackCount = 0;
        doneCallbackCalled = false;
    }

    static void simpleSequencerCallbackFunction(Sequencer &sequencer, uint8_t step) {
        functionCallbackCount++;
        std::cout << millis() << std::endl;
        switch (step) {
            case 1:
                sequencer.nextWithDelay(500);
                break;
            case 2:
                sequencer.nextWithDelay(1000);
                break;
            case 3:
                break;
        }
    }

    static void sequencerDoneCallbackFunction() {
        doneCallbackCalled = true;
    }

};


int FunctionSequencerTest::functionCallbackCount = 0;
bool FunctionSequencerTest::doneCallbackCalled = false;



TEST_F(FunctionSequencerTest, testCallbackSwitchFromFunctionToMethod) {
    FunctionCallback doneCallback(&FunctionSequencerTest::sequencerDoneCallbackFunction);
    FunctionSequencer sequencer(&FunctionSequencerTest::simpleSequencerCallbackFunction);

    ASSERT_EQ(0, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    sequencer.startSequence(1, &doneCallback);

    ASSERT_EQ(1, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(495);
    ASSERT_EQ(1, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(10);
    ASSERT_EQ(2, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(990);
    ASSERT_EQ(2, functionCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(10);
    ASSERT_EQ(3, functionCallbackCount);
    ASSERT_TRUE(doneCallbackCalled);

};


