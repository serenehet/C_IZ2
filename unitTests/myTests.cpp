#include "gtest/gtest.h"
#include <time.h>
#include <iostream>
#include <string.h>
extern "C" {
    #include "../parallelSolution/decisionParallel.h"
    #include "../consistentSolution/decisionConsistent.h"
}

TEST(testAll, test1) {
    char * arr = (char *)("a");
    size_t res1 = (giveMostPopularStrConsistent(arr, 1)).number;
    size_t res2 = (giveMostPopularStrParallel(arr, 1)).number;
    ASSERT_EQ(res1, res2);
}

TEST(testAll, test2) {
    char * arr = (char *)("abbccddeeuu");
    size_t res1 = (giveMostPopularStrConsistent(arr, 11)).number;
    size_t res2 = (giveMostPopularStrParallel(arr, 11)).number;
    ASSERT_EQ(res1, 2);
    ASSERT_EQ(res1, res2);
}


TEST(testAll, test3) {
    char * arr = (char *)("hgfdhgfdaaaabbbbccccddddkkkk\0");
    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
    ASSERT_EQ(res1, 4);
    ASSERT_EQ(res1, res2);
}
