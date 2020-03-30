//
// Created by Sergei Alexeev on 19.03.2020.
//

#ifndef C_IZ2_INFOCONTAINER_H
#define C_IZ2_INFOCONTAINER_H

#include <stdio.h>

typedef struct Info {
    char symbol;
    size_t number;
    int counter; // int нужен, так как в логике решения могут произойти случаи, когда один поток вычест 1 по своей проверке
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
