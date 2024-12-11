#include <iostream>

void read(char*& s) {
    while (true) {
        int i = 0;
        while (true) {
            s[i] = (char)getchar();
            if (s[i] == '\n') {
                s[i] = '\0';
                return;
            }
            i++;
        }
    }
}

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

void write(char*& s) {
    for (int i = 0; s[i] != '\0'; i++) {
        std::cout << s[i];
    }
    std::cout << '\n';
}
