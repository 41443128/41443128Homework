#include <iostream>
using namespace std;

int ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    if (n == 0)
        return ackermann(m - 1, 1);

    return ackermann(m - 1, ackermann(m, n - 1));
}

int ackermannLoop(int m, int n) {
    int s[100000];
    int top = 0;
    s[top++] = m;
    while (top > 0) {
        m = s[--top];

        if (m == 0) {
            n++;
        } else if (n == 0) {
            n = 1;
            s[top++] = m - 1;
        } else {
            s[top++] = m - 1;
            s[top++] = m;
            n--;
        }
    }
    return n;
}

int main() {
    int m = 2;
    int n = 3;
    cout << "Recursive: " << ackermann(m, n) << '\n';
    cout << "Non-recursive: " << ackermannLoop(m, n) << '\n';

    return 0;
}
