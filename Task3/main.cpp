#include <iostream>
#include "solve.h"

struct digit {
    int len = 0, n = 0;

    int place[10]{}, lim[10]{}, base[10]{};

    digit() = default;

    digit(int nn): n(nn) {
        int can = 36;
        len = 1;
        while (can < nn) {
            len++;
            can *= 36;
        }
        for (int i = 0; i < len; i++) {
            place[i] = 0;
        }
        int nx = nn;
        nn--;
        for (int i = 0; i < len + 1; i++) {
            lim[i] = nn % 36;
            base[i] = nx % 36;
            nn /= 36;
            nx /= 36;
        }
    }

    bool isZero() {
        for (int i = 0; i < len; i++) {
            if (place[i] != 0) {
                return false;
            }
        }
        return true;
    }

    void setOne() {
        for (int i = 0; i < len; i++) {
            place[i] = 0;
        }
        place[0] = 1;
    }

    void setZero() {
        for (int i = 0; i < len; i++) {
            place[i] = 0;
        }
    }

    void setLim() {
        for (int i = 0; i < len; i++) {
            place[i] = lim[i];
        }
    }

    void setBase() {
        for (int i = 0; i < len; i++) {
            place[i] = base[i];
        }
    }

    void read(char f) {
        int j = len - 1;
        place[j--] = numberByDigit(f);
        while (j >= 0) {
            char a = (char)getchar();
            if (a == '\n') {
                break;
            }
            else {
                place[j--] = numberByDigit(a);
            }
        }
    }

    void display(int* a) const {
        for (int i = len - 1; i >= 0; i--) {
            std::cout << digitByNumber(a[i]);
        }
    }

    void display() {
        display(place);
    }

    digit operator + (const digit& other) const {
        digit res(n);
        int overflow = 0;
        for (int i = 0; i < len + 1; i++) {
            int d = (place[i] + other.place[i] + overflow);
            res.place[i] = d % 36;
            overflow = d / 36;
        }
        return res;
    }

    digit operator - (const digit& other) const {
        digit res(n);
        int get = 0;
        for (int i = 0; i < len + 1; i++) {
            if (place[i] - (get + other.place[i]) >= 0) {
                res.place[i] = place[i] - (get + other.place[i]);
                get = 0;
            }
            else {
                res.place[i] = place[i] - (-36 + (get + other.place[i]));
                get = 1;
            }
        }
        return res;
    }

    bool operator > (const digit& other) const {
        for (int i = 0; i < len + 1; i++) {
            if (place[i] > other.place[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator < (digit other) {
        for (int i = len; i >= 0; i--) {
            if (place[i] < other.place[i]) {
                return true;
            }
        }
        return false;
    }
};

struct number {
    bool neg = false;
    int n, len;
    digit dg[100]{};

    number(int n): n(n) {
        for (auto &i : dg) {
            i = digit(n);
        }
    }

    void read() {
        char sign = (char)getchar();
        if (sign == '-') {
            neg = true;
        }
        len = 0;
        for (auto &u : dg) {
            char c = (char)getchar();
            if (c == '\n') {
                break;
            }
            len++;
            u.read(c);
        }
        for (int i = 0; i < len / 2; i++) {
            std::swap(dg[i], dg[len - i - 1]);
        }
    }

    void display() {
        if (neg) {
            std::cout << "-";
        }
        for (int i = len - 1; i >= 0; i--) {
            dg[i].display();
        }
    }

    bool operator < (number other) {
        for (int i = 99; i >= 0; i--) {
            if (dg[i] < other.dg[i]) {
                return true;
            }
        }
        return false;
    }

    void switchSign() {
        neg = !neg;
    }

    number operator + (number other) {
        if (neg != other.neg) {
            if (neg) {
                if (*this < other) {
                    number res = other - *this;
                    res.neg = false;
                    return res;
                }
                else {
                    number res = *this - other;
                    res.neg = true;
                    return res;
                }
            }
            else {
                if (other < *this) {
                    number res = *this - other;
                    return res;
                }
                else {
                    number res = other - *this;
                    res.neg = true;
                    return res;
                }
            }
        }
        number res(n);
        res.neg = neg;
        res.len = std::max(len, other.len);
        digit rem(n);
        for (int i = 0; i < res.len; i++) {
            res.dg[i] = dg[i] + other.dg[i] + rem;
            digit bs(n);
            bs.setLim();
            if (res.dg[i] > bs) {
                rem.setOne();
                bs.setBase();
                res.dg[i] = res.dg[i] - bs;
            }
            else {
                rem.setZero();
            }
        }
        if (!rem.isZero()) {
            res.dg[(res.len)++].setOne();
        }
        return res;
    }

    number operator - (number other) {
        number res(n);
        res.len = std::max(len, other.len);
        digit sub(n);
        digit base(n); base.setBase();
        for (int i = 0; i < len; i++) {
            if (!(dg[i] < sub + other.dg[i])) {
                res.dg[i] = dg[i] - (sub + other.dg[i]);
                sub.setZero();
            }
            else {
                res.dg[i] = dg[i] + base - (sub + other.dg[i]);
                sub.setOne();
            }
        }
        if (res.dg[res.len - 1].isZero()) {
            res.len--;
        }
        return res;
    }
};

int main() {
    std::cout << "Программа, реализующая сложение и вычитание длинных чисел в любой системе счисления.\n";
    while (true) {
        std::cout << "Введите основание системы счисления(отрицательное число, чтобы завершить работу программы).\n";
        int n;
        read(n);

        if (n < 0) {
            std::cout << "Конец.\n";
            break;
        }
        digit exm = digit(n);
        std::cout << "В данной системе счисления цифра - число в системе счисления 36 с количеством разрядов, "
                     "равным " << exm.len << " не больше числа ";
        exm.display(exm.lim);
        std::cout << "\n";

        std::cout << "Введите первое число.\n";
        number a(n);
        a.read();

        std::cout << "Введите второе число.\n";
        number b(n);
        b.read();

        std::cout << "Введите знак(+ или -).\n";
        char c = (char)getchar();

        if (c == '-') {
            b.switchSign();
        }

        number res = a + b;

        if (c == '-') {
            b.switchSign();
        }

        a.display();
        std::cout << " " << c << " ";
        b.display();
        std::cout << " = ";
        res.display();
        std::cout << '\n';

        getchar();
    }
}
