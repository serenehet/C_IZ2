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
    size_t n = 1024 * 1024 * 100;
    srand(time(NULL));
    char * arr = (char *)calloc(n + 1, sizeof(char));
    arr[n] = '\0';
    for(int i = 0; i < n; i++) {
        arr[i] = (char)((rand() % 26) + 97);
    }
    size_t res1 = (giveMostPopularStrConsistent(arr, n)).number;
    size_t res2 = (giveMostPopularStrParallel(arr, n)).number;
    free(arr);
    ASSERT_EQ(res1, res2);
}
