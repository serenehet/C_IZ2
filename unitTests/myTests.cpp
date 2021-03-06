#include "gtest/gtest.h"
#include <time.h>
#include <iostream>
#include <string.h>
extern "C" {
    #include "../parallelSolution/decisionParallel.h"
    #include "../consistentSolution/decisionConsistent.h"
}

TEST(testAll, test1) {
    const char * arr = "a";
    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
    ASSERT_EQ(res1, res2);
}

TEST(testAll, test2) {
    const char * arr = "abc";
    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
    ASSERT_EQ(res1, res2);
}

TEST(testAll, test3) {
    const char * arr = "abbccddeeuu";
    size_t res1 = (giveMostPopularStrConsistent(arr, strlen(arr))).number;
    size_t res2 = (giveMostPopularStrParallel(arr, strlen(arr))).number;
    ASSERT_EQ(res1, 2);
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

TEST(testAll, test5) {
    srand(time(NULL));
    int n = 500;
    char * arr = (char *)calloc(n, sizeof(char));
    for(int i = 0; i < n; ++i) {
    arr[i] = 't';
    }
    size_t res1 = (giveMostPopularStrConsistent(arr, n)).number;
    size_t res2 = (giveMostPopularStrParallel(arr, n)).number;
    free(arr);
    ASSERT_EQ(res1, n);
    ASSERT_EQ(res1, res2);
}

TEST(testAll, test6) {
    srand(time(NULL));
    int n = 50000;
    char * arr = (char *)calloc(n, sizeof(char));
    for(int i = 0; i < n; ++i) {
        arr[i] = 't';
    }
    size_t res1 = (giveMostPopularStrConsistent(arr, n)).number;
    size_t res2 = (giveMostPopularStrParallel(arr, n)).number;
    free(arr);
    ASSERT_EQ(res1, n);
    ASSERT_EQ(res1, res2);
}
