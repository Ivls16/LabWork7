#include <iostream>

bool div5(int);
bool div47(int);
bool div89(int);

int main() {
    std::cout << "Программа, проверяющая, делится ли заданное число на 5, 47 и 89.\n";
    while (true) {
        std::cout << "Введите число, для которого нужно проверить делимость"
                     "(отрицательное, чтобы завершить работу программы).\n";
        int n;
        std::cin >> n;
        if (n < 0) {
            std::cout << "Конец.\n";
            break;
        }
        if (div5(n)) {
            std::cout << "Число делится на 5.\n";
        }
        else {
            std::cout << "Число не делится на 5.\n";
        }
        if (div47(n)) {
            std::cout << "Число делится на 47.\n";
        }
        else {
            std::cout << "Число не делится на 47.\n";
        }
        if (div89(n)) {
            std::cout << "Число делится на 89.\n";
        }
        else {
            std::cout << "Число не делится на 89.\n";
        }
    }
}

bool div5(int a) {
    while (abs(a) > 5) {
        int b = (a >> 1);
        for (int i = 0; i < 3; i++) {
            b += a & 1;
        }
        a = b;
    }
    return abs(a) == 5 || abs(a) == 0;
}

bool div47(int a) {
    while (abs(a) > 47) {
        int b = (a >> 2);
        for (int i = 0; i < 12; i++) {
            b += a & 3;
        }
        a = b;
    }
    return abs(a) == 47 || abs(a) == 0;
}

bool div89(int a) {
    while (abs(a) > 89) {
        int b = (a >> 1);
        for (int i = 0; i < 45; i++) {
            b += a & 1;
        }
        a = b;
    }
    return abs(a) == 89 || abs(a) == 0;
}