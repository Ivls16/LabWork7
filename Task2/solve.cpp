#include <iostream>
#include "solve.h"

void completeTo(char*& a, int& n, int m) {
    int delta = m - n;
    for (int i = n; i >= 1; i--) {
        a[i + delta] = a[i];
    }
    for (int i = delta; i > 0; i--) {
        a[i] = '0';
    }
    n = m;
}

void shiftRight(char*& a, int& n) {
    for (int i = n; i >= 0; i--) {
        a[i + 1] = a[i];
    }
    a[0] = '0';
    n++;
}

void shiftLeft(char*& a, int& n) {
    for (int i = 0; i < n; i++) {
        a[i] = a[i + 1];
    }
    n--;
}

void divideBy2(char*& a, int &n) {
    for (int i = n - 1; i >= 0; i--) {
        int di = (int)a[i] - (int)'0';
        if (i) {
            a[i - 1] = (char)((int)a[i - 1] + di % 2 * 10);
        }
        a[i] = (char)((int)'0' + di / 2);
    }
    for (int i = n - 1; i > 0 && a[i] == '0'; i--) {
        a[n - 1] = '\0';
        n--;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

void add(char*& res, int& nr, char*& a, int n, char*& b, int m) {
    reverse(a, n);
    reverse(b, m);
    int pl = 0;
    for (int i = 0; i < max(n, m); i++) {
        int aa = (i >= n ? '0' : a[i] - '0');
        int bb = (i >= m ? '0' : b[i] - '0');
        res[i] = (char)((int)'0' + (aa + bb + pl) % 2);
        pl = (aa + bb + pl) / 2;
    }
    nr = max(n, m);
    if (pl) {
        res[nr] = '1';
        nr++;
    }
    res[nr] = '\0';
    reverse(res, nr);
}

void real_to_straight(char*& a, int n, char*& as, int& ns) {
    if (a[0] < '0' || a[0] > '9') {
        as[ns++] = '1';
        n--;
        for (int i = 0; a[i] != '\0'; i++) {
            a[i] = a[i + 1];
        }
    }
    else {
        as[ns++] = '0';
    }
    reverse(a, n);
    while (n > 1 || a[0] != '0') {
        as[ns++] = (char)('0' + (a[0] - '0') % 2);
        divideBy2(a, n);
    }
    reverse1(as, ns);
}

void straight_to_add(char*& a, int n) {
    if (a[0] == '0') {
        return;
    }
    for (int i = 1; i < n; i++) {
        a[i] = (char)('0' + '1' - a[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == '1') {
            a[i] = '0';
        }
        else {
            a[i] = '1';
            break;
        }
    }
}

void add(char*& a, char*& b, int& n, int& m) {
    if (m > n) {
        n = m;
        a[n] = '\0';
        for (int i = n - 1; i > 0; i--) {
            if (a[i] >= '1' && a[i] <= '9') {
                break;
            }
            a[i] = '0';
        }
    }
    int pl = 0;
    for (int i = 0; i < n; i++) {
        int da = a[i] - '0';
        int db = b[i] - '0';
        a[i] = (char)((int)'0' + (da + db + pl) % 10);
        pl = (da + db + pl) / 10;
    }
    if (pl > 0) {
        n++;
        a[n - 1] = '1';
        a[n] = '\0';
    }
}

void add_to_real(char*& sum, int n, char*& ans, int& nans) {
    bool neg = false;
    if (sum[0] == '1') {
        neg = true;
        for (int i = n - 1; i >= 0; i--) {
            if (sum[i] == '1') {
                sum[i] = '0';
                break;
            }
            else {
                sum[i] = '1';
            }
        }
        for (int i = 0; i < n; i++) {
            sum[i] = (char)((int)'0' + '1' - sum[i]);
        }
    }
    write(sum, n);
    ans[nans++] = '0';
    reverse(sum, n--);
    char* p2 = new char[200];
    p2[0] = '1'; p2[1] = '\0';
    int m = 1;
    for (int i = 0; i < n; i++) {
        if (sum[i] == '1') {
            add(ans, p2, nans, m);
        }
        add(p2, p2, m, m);
    }
    ans[nans] = '\0';
    reverse(ans, nans);
    if (neg) {
        shiftRight(ans, nans);
        ans[0] = '-';
    }
    delete[] p2;
}