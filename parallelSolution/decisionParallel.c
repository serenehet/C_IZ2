#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../parallelSolution/decisionParallel.h"

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define BAD_MESSAGE         -13
#define SUCCESS               0

pthread_mutex_t mutex;

void * checkPart(void *args) {
    Args * arg = (Args *)args;
    InfoContainer * container = arg->container;
    size_t start = arg->start;
    size_t end = arg->end;
    char * arr = arg->arr;
    size_t size = arg->size;

    if (start >= end) { return SUCCESS; }
    size_t n = 1;
    char temp = arr[start];
    for (size_t i = start + 1; i <= end; ++i) {
        if (arr[i] == temp) {
            ++n;
        } else {
            pthread_mutex_lock(&mutex);
            Info * info = getElement(container, n);
            if (info != NULL) {
                info->number = n;
                info->symbol = arr[i - 1];
                info->counter += 1;
            }
            pthread_mutex_unlock(&mutex);
            n = 1;
        }
        temp = arr[i];
    }
    //проверка граничных условий
    if (end >= size - 1) { return SUCCESS;}
    if (arr[end + 1] != arr[end]) { return SUCCESS; }

    size_t j = end - 1;
    size_t c1 = 0;
    while ((j >= 0) && (arr[j] == arr[j + 1])) {
        ++c1;
        --j;
    }
    pthread_mutex_lock(&mutex);
    Info * info = getElement(container, c1);
    if (info != NULL) {
        info->counter -= 1;
    }
    pthread_mutex_unlock(&mutex);
    j = end + 1;
    size_t c2 = 0;
    while (((j + 1) < size) &&(arr[j] == arr[j + 1])) {
        ++c2; ++j;
    }

    pthread_mutex_lock(&mutex);
    info = getElement(container, c1);
    if (info != NULL) {
        --(info->counter);
    }
    info = getElement(container, c1 + c2);
    if (info != NULL) {
        ++(info->counter);
    }
    pthread_mutex_unlock(&mutex);
    // граничные усовия проверены)
    return SUCCESS;
}

Info giveMostPopularStrParallel(const char * const arr, size_t size) {
    if (size == 0) {
        Info error;
        error.number = 0;
        error.symbol = '\0';
        error.counter = 0;
        return error;
    }
    pthread_mutex_init(&mutex, NULL);

    size_t numberThreads = sysconf(_SC_NPROCESSORS_ONLN);

    InfoContainer container = createInfoContainer();

    pthread_t * threads = (pthread_t *)calloc(numberThreads, sizeof(pthread_t));
    int status = 0, i = 0;
    Args * args = (Args *)calloc(numberThreads, sizeof(Args));

    size_t part = size;
    if (numberThreads > 1) {
        part = (size / numberThreads) + 1;
    }
    size_t index = 0;

    for (i = 0; i < numberThreads; i++) {
        args[i].arr = (char *)arr;
        args[i].container = &container;
        args[i].start = index;
        size_t end = index + part;
        index += part;
        if (end > size - 1) { end = size - 1; };
        if (index > size - 1) {index = size - 1; };
        args[i].end = end;
        args[i].size = size;
    }

    for (i = 0; i < numberThreads; i++) {
        status = pthread_create(&threads[i], NULL, checkPart, (void*) &args[i]);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(ERROR_CREATE_THREAD);
        }
    }

    for (i = 0; i < numberThreads; i++) {
        status = pthread_join(threads[i], NULL);
        if (status != SUCCESS) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(ERROR_JOIN_THREAD);
        }
    }
    free(threads);
    free(args);
    pthread_mutex_destroy(&mutex);
    Info res = giveInfoMostPopular(&container);
    freeContainer(&container);
    return res;
}
