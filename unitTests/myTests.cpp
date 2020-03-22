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
    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
    ASSERT_EQ(res1, res2);
}

TEST(testAll, test2) {
    char * arr = (char *)("abbccddeeuu");
    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
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

char * getStr(size_t n) {
    srand(time(NULL));
    char * arr = (char *)calloc(n + 1, sizeof(char));
    arr[n] = '\0';
    for(int i = 0; i < n; i++) {
        arr[i] = (char)((rand() % 3) + 99);
    }
    return arr;
}

TEST(testAll, test4) {
    srand(time(NULL));
    int n = 4900;
    char * arr = (char *)calloc(n, sizeof(char));
    int k = 49;
    int i = 0;
    char temp = (char)((rand() % 26) + 99);
    while (i < n) {
        if (i % k == 0) {
            temp = (char)((rand() % 26) + 99);
        }
        arr[i++] = temp;
    }

    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
    free(arr);
    ASSERT_EQ(res1, k);
    ASSERT_EQ(res1, res2);
}
