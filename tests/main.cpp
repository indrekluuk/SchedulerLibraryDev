#include <stdio.h>
#include <cstdio>
#include "gtest/gtest.h"




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    //std::getchar();
    return result;
}
