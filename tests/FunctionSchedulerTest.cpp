#include <gtest/gtest.h>
#include <Scheduler.h>
#include <Arduino.h>






class FunctionSchedulerTest : public ::testing::Test {
protected:

    static bool callbackCalled;

    virtual void SetUp() {
        callbackCalled = false;
    }

    static void schedulerCallbackFunction() {
        callbackCalled = true;
    }

    void runScheduler(uint32_t time_ms) {
        arduino_increase_millis(time_ms);
        Scheduler::run();
    }
};

bool FunctionSchedulerTest::callbackCalled = false;



TEST_F(FunctionSchedulerTest, testPeriodicalCallback) {

    FunctionScheduler scheduler(FunctionSchedulerTest::schedulerCallbackFunction);

    scheduler.runOnce(500);
    runScheduler(495);
    ASSERT_FALSE(callbackCalled);
    runScheduler(10);
    ASSERT_TRUE(callbackCalled);
};

