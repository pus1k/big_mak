#include <cmath>
#include <iostream>

int N = 3;

using std::cin;
using std::cout;
using std::endl;

void progon(double* a, double* b, double* c, double* d)
{
    double A[N - 1];
    double B[N];
    // Прямой ход
    double x[N] = { 0 };
    A[0] = -1 * (c[0] / b[0]);

    if (d[0] != 0)
        B[0] = d[0] / b[0];
    else
        B[0] = 0;

    for (int j = 1; j < N - 1; j++) {
        A[j] = -1 * (c[j] / (b[j] + a[j] * A[j - 1]));
        B[j] = (d[j] - a[j] * B[j - 1]) / (b[j] + a[j] * A[j - 1]);
    }

    B[N - 1] = (d[N - 1] - a[N - 1] * B[N - 2]) / (b[N - 1] + a[N - 1] * A[N - 2]);

    // Обратный ход
    x[N - 1] = B[N - 1];
    for (int i = N - 2; i > -1; i--) {
        x[i] = A[i] * x[i + 1] + B[i];
    }
    // Вывод ответа
    for (int i = 0; i < N; i++) {
        cout << "X[" << i + 1 << "] = " << round(x[i] * 100) / 100 << " ";
    }
    cout << endl;
}

int main()
{
    double a[N];
    double b[N];
    double c[N];
    double x[N];
    int ans;
    std::cout << "Do you wanna fill your matrix by yourself:" << std::endl;
    std::cout << "1) Yes" << std::endl;
    std::cout << "2) Use template" << std::endl;
    std::cin >> ans;
    if (ans == 2 && N == 3) {
        a[0] = 0, a[1] = 5, a[2] = 1;
        b[0] = 2, b[1] = 4, b[2] = -3;
        c[0] = -1, c[1] = 2, c[2] = 0;
        x[0] = 3, x[1] = 6, x[2] = 2;
    } else {
        for (int i = 0, j = 1, offset = 0; i < N; i++, j++) {
            if (i > 1) {
                offset++;
            }
            cout << "a[" << j << "][" << 1 + offset << "] = ";
            if (i == 0) {
                cin >> b[i];
                cout << "a[" << j << "][" << offset + 2 << "] = ";
                cin >> c[i];
            } else if (i == N - 1) {
                cin >> a[i];
                cout << "a[" << j << "][" << j << "] = ";
                cin >> b[i];
            } else {
                cin >> a[i];
                cout << "a[" << j << "][" << offset + 2 << "] = ";
                cin >> b[i];
                cout << "a[" << j << "][" << offset + 3 << "] = ";
                cin >> c[i];
            }
        }
        for (int i = 0; i < N; ++i) {
            cout << "X[" << i + 1 << "] = ";
            cin >> x[i];
        }
        cout << endl;
    }

    for (int i = 0, offset = 0, count = 0; i < N; i++) {
        if (i > 1)
            offset++;
        for (int j = 0; j < offset; j++) {
            cout << "0 ";
        }
        if (i == 0) {
            cout << b[0] << " " << c[0] << " ";
            count = 2;
        } else if (i == N - 1) {
            count = 2;
            cout << a[i] << " " << b[i] << " ";
        } else {
            cout << a[i] << " " << b[i] << " " << c[i] << " ";
            count = 3;
        }
        for (int j = offset + count; j < N; j++) {
            cout << "0 ";
        }

        cout << endl;
    }

    progon(a, b, c, x);
    return 0;
}