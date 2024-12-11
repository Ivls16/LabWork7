#include <iostream>

void read(char*& s, int& n) {
    while (true) {
        int i = 0;
        while (true) {
            s[i] = (char)getchar();
            if (s[i] == '\n') {
                n = i;
                s[i] = '\0';
                return;
            }
            if (!isdigit(s[i]) && !(i == 0 && s[i] == '-')) {
                std::cout << "Неверный ввод.\n";
                while (getchar() != '\n') {}
                break;
            }
            i++;
        }
    }
}

void reverse(char*& a, int n) {
    for (int i = 0; i < n / 2; i++) {
        char temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
}

void reverse1(char*& a, int n) {
    for (int i = 1; i < (n + 1) / 2; i++) {
        char temp = a[i];
        a[i] = a[n - i];
        a[n - i] = temp;
    }
}

void write(char*& a, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i];
    }
    std::cout << '\n';
}