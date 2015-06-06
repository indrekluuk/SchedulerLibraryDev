cmake_minimum_required(VERSION 3.2)
project(SchedulerLibraryDev)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # -std=c++11


include_directories("./external_src")
include_directories("./sketch_Scheduler")


set(EXT_SOURCE_FILES
    external_src/Arduino.cpp
    external_src/main.cpp
    external_src/Arduino.h
)


set(LIB_SOURCE_FILES
    sketch_Scheduler/Callback.h
    sketch_Scheduler/Scheduler.cpp
    sketch_Scheduler/Scheduler.h
    sketch_Scheduler/SchedulerGlobals.h
    sketch_Scheduler/Sequencer.cpp
    sketch_Scheduler/Sequencer.h
)


add_executable(SchedulerLibraryDev ${EXT_SOURCE_FILES} ${LIB_SOURCE_FILES})


# copy library items to export dir
add_custom_command(
    TARGET SchedulerLibraryDev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/export
)
add_custom_command(
    TARGET SchedulerLibraryDev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/export
)
foreach( file_i ${LIB_SOURCE_FILES})
    add_custom_command(
        TARGET SchedulerLibraryDev POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${file_i} ${CMAKE_SOURCE_DIR}/export
    )
endforeach( file_i )



