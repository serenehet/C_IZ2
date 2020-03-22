//Сравните и выведите в консоль время работы последовательного
//и параллельного с использованием нескольких потоков алгоритмов,
//каждый из которых выделяет в динамической памяти символьный массив размером 100 Мб
//и подсчитывает количество серий повторяющихся символов разной длины,
//после чего выводит представителя серии самой часто встречаемой длины.

// считаю, что 1 символ не является повторением
#include <stdio.h>
#include <stdlib.h>
#include "../parallelSolution/decisionParallel.h"
#include "../consistentSolution/decisionConsistent.h"
#include <time.h>
#include <sys/time.h>

char * getRandomStr(size_t n);
void printRes(Info * popularInfo);
void printTimeDz(size_t n);

int main() {
    printTimeDz(100);
    printTimeDz(1000);
    printTimeDz(10000);
    printTimeDz(100000);
    printTimeDz(1000000);
    return 0;
}

char * getRandomStr(size_t n) {
    srand(time(NULL));
    char * arr = (char *)calloc(n + 1, sizeof(char));
    arr[n] = '\0';
    for(int i = 0; i < n; i++) {
        arr[i] = (char)((rand() % 3) + 99);
    }
    return arr;
}

void printRes(Info * popularInfo) {
    printf("%zu\n", popularInfo->number);
    for(size_t i = 0; i < popularInfo->number; ++i) {
        printf("%c", popularInfo->symbol);
    }
    printf("\n");
}

void printTimeDz(size_t n) {
    printf("---\n");
    struct timeval stop, start;
    char * arr = getRandomStr(n);
    Info res;
    //последовательное решение
    double mkrSec = 1000000.0;
    gettimeofday(&start, NULL);
    res = giveMostPopularStrConsistent(arr, n);
    gettimeofday(&stop, NULL);
    printf("time consistent %zu byte - %f\n", n, (double)(stop.tv_usec - start.tv_usec) / mkrSec);
    //паралельное решение
    gettimeofday(&start, NULL);
    res = giveMostPopularStrParallel(arr, n);
    gettimeofday(&stop, NULL);
    printf("time parallel %zu byte - %f\n", n, (double)(stop.tv_usec - start.tv_usec) / mkrSec);
    free(arr);
    printf("---\n");
}
