//
// Created by Sergei Alexeev on 19.03.2020.
//

#ifndef C_IZ2_INFOCONTAINER_H
#define C_IZ2_INFOCONTAINER_H

#include <stdio.h>

typedef struct Info {
    char symbol;
    size_t number;
    size_t counter;
} Info;

typedef struct InfoContainer {
    size_t size;
    Info *arr;
} InfoContainer;

InfoContainer createInfoContainer();
Info * getElement(InfoContainer * container, size_t index); // если вышел за размер контейнера, он увеличвается и всё равно отдает указатель на элемент
Info giveInfoMostPopular(InfoContainer * container);
void freeContainer(InfoContainer * container);

#endif //C_IZ2_INFOCONTAINER_H
