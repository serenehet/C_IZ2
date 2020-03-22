//
// Created by Sergei Alexeev on 19.03.2020.
//

#include "../consistentSolution/decisionConsistent.h"

Info giveMostPopularStrConsistent(const char * const arr, size_t size) {
    if (size == 0 || arr == NULL) {
        Info error;
        error.number = 0;
        error.symbol = '\0';
        error.counter = 0;
        return error;
    }
    InfoContainer container = createInfoContainer();
    size_t n = 1;
    for (size_t i = 1; i <= (size - 1); ++i) {
        if (arr[i] == arr[i - 1]) { ++n; }
        else {
            Info * info = getElement(&container, n);
            if (info != NULL) {
                info->number = n;
                info->symbol = arr[i - 1];
                info->counter += 1;
            }
            n = 1;
        }
    }
    Info res = giveInfoMostPopular(&container);
    freeContainer(&container);
    return res;
}

