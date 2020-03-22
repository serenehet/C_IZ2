//
// Created by Sergei Alexeev on 19.03.2020.
//

#ifndef C_IZ2_DECISIONPARALLEL_H
#define C_IZ2_DECISIONPARALLEL_H

#include "../infoContainer/infoContainer.h"

typedef struct Args {
    InfoContainer * container;
    char * arr;
    size_t start;
    size_t end;
    size_t size;
} Args;

void * checkPart(void *args);
Info giveMostPopularStrParallel(const char * const arr, size_t size);

#endif //C_IZ2_DECISION_H
