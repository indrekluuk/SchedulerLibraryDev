#include "SchedulerTestBase.h"
#include "Sequencer.h"





class MethodSequencerTest : public SchedulerTestBase {
protected:

    int methodCallbackCount;
    bool doneCallbackCalled;

    virtual void SetUp() {
        methodCallbackCount = 0;
        doneCallbackCalled = false;
    }

public:

    void simpleSequencerCallbackMethod(Sequencer &sequencer, uint8_t step) {
        methodCallbackCount++;
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

    void sequencerDoneCallbackMethod() {
        doneCallbackCalled = true;
    }

};



TEST_F(MethodSequencerTest, testCallbackSwitchFromFunctionToMethod) {
    MethodCallback<MethodSequencerTest> doneCallback(this, &MethodSequencerTest::sequencerDoneCallbackMethod);
    MethodSequencer<MethodSequencerTest> sequencer(this, &MethodSequencerTest::simpleSequencerCallbackMethod);

    ASSERT_EQ(0, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    sequencer.startSequence(1, &doneCallback);

    ASSERT_EQ(1, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(495);
    ASSERT_EQ(1, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(10);
    ASSERT_EQ(2, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(990);
    ASSERT_EQ(2, methodCallbackCount);
    ASSERT_FALSE(doneCallbackCalled);

    runScheduler(10);
    ASSERT_EQ(3, methodCallbackCount);
    ASSERT_TRUE(doneCallbackCalled);

};


