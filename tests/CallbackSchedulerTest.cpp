#include "SchedulerTestBase.h"



class CallbackSchedulerTest : public SchedulerTestBase {
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

int CallbackSchedulerTest::functionCallbackCount = 0;



TEST_F(CallbackSchedulerTest, testCallbackSwitchFromFunctionToMethod) {
    FunctionCallback functionCallback(&CallbackSchedulerTest::schedulerCallbackFunction);
    MethodCallback<CallbackSchedulerTest> methodCallback(this, &CallbackSchedulerTest::schedulerCallbackMethod);

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


