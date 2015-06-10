cmake_minimum_required(VERSION 3.2)
project(SchedulerLibraryDev)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # -std=c++11


include_directories("tests")
include_directories("./sketch_Scheduler")
include_directories("./frameworks")


set(SOURCE_FILES
    sketch_Scheduler/Callback.h
    sketch_Scheduler/Scheduler.cpp
    sketch_Scheduler/Scheduler.h
    sketch_Scheduler/SchedulerGlobals.h
    sketch_Scheduler/Sequencer.cpp
    sketch_Scheduler/Sequencer.h
)

set(TEST_SOURCE_FILES
    tests/Arduino.cpp
    tests/Arduino.h
    tests/main.cpp
    tests/SchedulerTestBase.h
    tests/FunctionSchedulerTest.cpp
    tests/MethodSchedulerTest.cpp
)

set(GTEST_SOURCE_FILES
    frameworks/gtest/gtest-all.cc
    frameworks/gtest/gtest.h
)



add_executable(SchedulerLibraryDev ${SOURCE_FILES} ${GTEST_SOURCE_FILES} ${TEST_SOURCE_FILES} tests/CallbackSchedulerTest.cpp tests/FunctionSequencerTest.cpp)





# copy library items to export dir
add_custom_command(
    TARGET SchedulerLibraryDev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/export
)
add_custom_command(
    TARGET SchedulerLibraryDev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/export/Scheduler
)
foreach( file_i ${LIB_SOURCE_FILES})
    add_custom_command(
        TARGET SchedulerLibraryDev POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${file_i} ${CMAKE_SOURCE_DIR}/export/Scheduler
    )
endforeach( file_i )
    add_custom_command(
        TARGET SchedulerLibraryDev POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples ${CMAKE_SOURCE_DIR}/export/Scheduler/examples
    )



