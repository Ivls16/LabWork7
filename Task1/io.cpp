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
            if (s[i] != '0' && s[i] != '1') {
                std::cout << "Неверный ввод.\n";
                while (getchar() != '\n') {}
                break;
            }
            i++;
        }
    }
}