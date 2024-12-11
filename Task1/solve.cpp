void sub1(char*& a, int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == '0') {
            a[i] = '1';
        }
        else {
            a[i] = '0';
            break;
        }
    }
}