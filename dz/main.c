//Сравните и выведите в консоль время работы последовательного
//и параллельного с использованием нескольких потоков алгоритмов,
//каждый из которых выделяет в динамической памяти символьный массив размером 100 Мб
//и подсчитывает количество серий повторяющихся символов разной длины,
//после чего выводит представителя серии самой часто встречаемой длины.
#include <stdio.h>
#include <stdlib.h>
#include "../parallelSolution/decision.h"
#include "../consistentSolution/decision.h"
#include <time.h>
#include <string.h>
#include <decision.h>

char * getRandomStr(size_t n);
void printRes(Info * popularInfo);

int main() {
    //последовательное решение
    size_t n = 10;
    char * arr = getRandomStr(n);
//    Info res = giveMostPopularStrConsistent(arr, 10);
    Info res = giveMostPopularStrParallel(arr, n);
    printRes(&res);
    return 0;
}

char * getRandomStr(size_t n) {
    srand(time(NULL));
    char * kek = (char *)calloc(n + 1, sizeof(char));
    kek[n] = '\0';
    for(int i = 0; i < n; i++) {
        kek[i] = (char)((rand() % 3) + 99);
    }
    return kek;
}

void printRes(Info * popularInfo) {
    printf("%zu\n", popularInfo->number);
    for(size_t i = 0; i < popularInfo->number; ++i) {
        printf("%c", popularInfo->symbol);
    }
}
