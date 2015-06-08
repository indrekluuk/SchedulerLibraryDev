#include "SchedulerTestBase.h"






class MethodSchedulerTest : public SchedulerTestBase {
protected:

    int callbackCount;

    virtual void SetUp() {
        callbackCount = 0;
    }

public:

    void schedulerCallbackMethod() {
        callbackCount++;
    }

};




TEST_F(MethodSchedulerTest, testCallOnceCallback) {

    MethodScheduler<MethodSchedulerTest> scheduler(this, &MethodSchedulerTest::schedulerCallbackMethod);

    scheduler.runOnce(500);
    runScheduler(495);
    ASSERT_EQ(0, callbackCount);
    runScheduler(10);
    ASSERT_EQ(1, callbackCount);
    runScheduler(500);
    ASSERT_EQ(1, callbackCount);
};



TEST_F(MethodSchedulerTest, testPeriodicalCallback) {

    MethodScheduler<MethodSchedulerTest> scheduler(this, &MethodSchedulerTest::schedulerCallbackMethod);

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




TEST_F(MethodSchedulerTest, testInitFunctionLater) {

    MethodScheduler<MethodSchedulerTest> scheduler;

    scheduler.runOnce(500);
    runScheduler(510);
    ASSERT_EQ(0, callbackCount);

    scheduler.set(this).runOnce(500);
    runScheduler(510);
    ASSERT_EQ(0, callbackCount);

    scheduler.set(&MethodSchedulerTest::schedulerCallbackMethod).runPeriodically(500);
    runScheduler(510);
    ASSERT_EQ(1, callbackCount);
    runScheduler(500);
    ASSERT_EQ(2, callbackCount);
};

