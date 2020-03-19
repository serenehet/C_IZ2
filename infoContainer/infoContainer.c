//
// Created by Sergei Alexeev on 19.03.2020.
//

#include "infoContainer.h"
#include <stdlib.h>

const size_t delta = 2; // не храним информации о повторениях 0 или 1 раз;

InfoContainer createInfoContainer() {
    InfoContainer container;
    container.size = 0;
    container.arr = NULL;
    return container;
}

Info * getElement(InfoContainer * container, size_t index) {
    if (index < 2) { return NULL; }
    if ((index - delta + 1) > container->size) {
        Info * temp = container->arr;
        Info * key = (Info *)realloc(container->arr, (index - delta + 1) * sizeof(Info));
        if (key == NULL) { container->arr = temp; return NULL; }
        container->size = (index - delta + 1);
        container->arr = key;
        container->arr[index - delta].number = index;
    }
    return &(container->arr[index - delta]);
}

Info giveInfoMostPopular(InfoContainer * container) {
    if (container->size == 0) { Info errorInfo = {'0', 0, 0}; return errorInfo; }
    Info popular = container->arr[0];
    for(size_t i = 1; i < container->size; ++i) {
        if (container->arr[i].counter > popular.counter) {
            popular = container->arr[i];
        }
    }
    return popular;
}
void freeContainer(InfoContainer * container) {
    free(container->arr);
    container->size = 0;
}
