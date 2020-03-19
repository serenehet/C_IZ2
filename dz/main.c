#include <stdio.h>
#include "../infoContainer/infoContainer.h"

int main() {
    InfoContainer test = createInfoContainer();
    Info * info = getElement(&test, 5);
    info->number = 5;
    info->counter = 3;
    info = getElement(&test, 2);
    info->number = 2;
    info->counter = 1;
    info = getElement(&test, 9);
    info->number = 9;
    info->counter = 6;
    printf("%zu\n", test.size);
    printf("%zu", giveInfoMostPopular(&test).number);
    return 0;
}
