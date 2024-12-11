#include <iostream>
#include "solve.h"

int main() {
    std::cout << "\nПрограмма, складывающая два числа, заданные в естественной форме "
                 "проводя сложение в дополнительной форме и выводящая результат в естественной.\n\n";
    while (true) {
        std::cout << "-----------------------------------------------------------------------------------------------\n";

        std::cout << "\nВведите первое слагаемое, представленное в естественной форме(пустое, чтобы завершить работы программы).\n";
        char* a = new char[200];
        int n;
        read(a, n);
        if (a[0] == '\0') {
            std::cout << "Конец.\n";
            break;
        }

        std::cout << "Введите второе слагаемое, представленное в естественной форме.\n";
        char* b = new char[200];
        int m;
        read(b, m);

        char *as = new char[200];
        int ns = 0;
        real_to_straight(a, n, as, ns);

        char *bs = new char[200];
        int ms = 0;
        real_to_straight(b, m, bs, ms);

        completeTo(as, ns, max(ns, ms));
        completeTo(bs, ms, max(ns, ms));

        std::cout << '\n';
        std::cout << "Первое слагаемое в прямом коде: ";
        write(as, ns);
        std::cout << "Второе слагаемое в прямом коде: ";
        write(bs, ms);
        std::cout << '\n';

        std::cout << "Первое слагаемое в дополнительном коде: ";
        straight_to_add(as, ns);
        write(as, ns);

        std::cout << "Второе слагаемое в дополнительном коде: ";
        straight_to_add(bs, ms);
        write(bs, ms);

        std::cout << '\n';
        std::cout << "Их сумма в дополнительном коде равна: ";
        char *sum = new char[200];
        int nsu = 0;
        if (as[0] == '0' && bs[0] == '0') {
            add(sum, nsu, as, ns, bs, ms);
            if (sum[0] == '1') {
                shiftRight(sum, nsu);
            }
        }
        else if (as[0] == '1' && bs[0] == '1') {
            add(sum, nsu, as, ns, bs, ms);
        }
        else {
            add(sum, nsu, as, ns, bs, ms);
            if (nsu > max(ns, ms)) {
                shiftLeft(sum, nsu);
            }
        }
        write(sum, nsu);

        std::cout << "\nИх сумма в естественной форме равна: ";
        char *ans = new char[200];
        int nans = 0;
        add_to_real(sum, nsu, ans, nans);
        write(ans, nans);
        std::cout << '\n';

        delete[] a;
        delete[] as;
        delete[] b;
    }
}
