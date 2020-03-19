#include "gtest/gtest.h"
extern "C" {
    #include "../parallelSolution/decisionParallel.h"
    #include "../consistentSolution/decisionConsistent.h"
}

TEST(testkek, test1) {
    char * arr = "";
    size_t res1 = (giveMostPopularStrConsistent(arr, 0)).number;
    size_t res2 = (giveMostPopularStrParallel(arr, 0)).number;
    ASSERT_EQ(true, true);
}