//
// Created by indrek on 8.06.2015.
//

#ifndef SCHEDULERLIBRARYDEV_SCHEDULERTESTBASE_H
#define SCHEDULERLIBRARYDEV_SCHEDULERTESTBASE_H


#include <gtest/gtest.h>
#include <Scheduler.h>
#include <Arduino.h>

class SchedulerTestBase : public ::testing::Test {
protected:

    static void runScheduler(uint32_t time_ms) {
        arduino_increase_millis(time_ms);
        Scheduler::run();
    }

};


#endif //SCHEDULERLIBRARYDEV_SCHEDULERTESTBASE_H