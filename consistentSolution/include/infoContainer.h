//
// Created by Sergei Alexeev on 19.03.2020.
//

#ifndef C_IZ2_INFOCONTAINER_H
#define C_IZ2_INFOCONTAINER_H

#include <stdio.h>

typedef struct Info {
    char symbol;
    int number;
    int counter;
} Info;

typedef struct InfoContainer {
    size_t size;
    Info *arr;
} InfoContainer;

InfoContainer createInfoContainer(void);

#endif //C_IZ2_INFOCONTAINER_H
