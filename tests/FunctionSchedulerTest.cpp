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
