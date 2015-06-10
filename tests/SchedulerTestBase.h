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
        for (int i=0; i<time_ms; i++) {
            arduino_increase_millis(1);
            Scheduler::run();
        }
    }

};


#endif //SCHEDULERLIBRARYDEV_SCHEDULERTESTBASE_H
