#include "iostream"

void read(int& n) {
    n = 0;
    while (true) {
        char c = (char)getchar();
        if (c == '\n') {
            return;
        }
        n = n * 10 + c - '0';
    }
}