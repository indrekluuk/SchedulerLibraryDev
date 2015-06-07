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

};

bool FunctionSchedulerTest::callbackCalled = false;



TEST_F(FunctionSchedulerTest, testPeriodicalCallback) {

    FunctionScheduler scheduler(FunctionSchedulerTest::schedulerCallbackFunction);

    scheduler.runOnce(500);

    arduino_increase_millis(495);
    Scheduler::run();
    ASSERT_FALSE(callbackCalled);
    arduino_increase_millis(10);
    Scheduler::run();
    ASSERT_TRUE(callbackCalled);
};

