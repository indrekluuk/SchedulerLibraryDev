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


