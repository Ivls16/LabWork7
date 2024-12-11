#include "solve.h"

const char* allDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char digitByNumber(int a) {
    return allDigits[a];
}

int numberByDigit(char a) {
    for (int i = 0; i < 36; i++) {
        if (allDigits[i] == a) {
            return i;
        }
    }
    return -1;
}