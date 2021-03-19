#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

double func(double x)
{
    return x * x * x + 3 * x * x + 3 * x + 1;
}

double Lagrange(double X, double* x, double* y, int size)
{
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        double temp = 1; // слогаемое полинома
        for (int j = 0; j < size; j++) {
            if (j != i) { // условие для исключения появления 0 в знаменателе
                temp *= (X - x[j]) / (x[i] - x[j]);
            }
        }
        result += temp * y[i];
    }
    return result;
}

void get_f(double** f, double* x, double* y, int size)
{
    int n = size - 1;
    int row = 0;
    for (int i = 0; i < n; i++)
        f[row][i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    row++, n--;
    while (row < size - 1) {
        for (int j = 0; j < n; j++) {
            f[row][j] = (f[row - 1][j + 1] - f[row - 1][j]) / (x[row + j + 1] - x[j]);
        }
        row++, n--;
    }
    // cout << "Value of table difference:" << endl;
    // for (int i = 0; i < size - 1; i++) {
    //     for (int j = 0; j < size - 1; j++)
    //         cout << std::setw(15) << f[i][j];
    //     cout << endl;
    // }
}

double Niuton(double X, double* x, double* y, int size)
{
    double result = y[0];
    double** f = new double*[size - 1];
    for (int i = 0; i < size - 1; i++) {
        f[i] = new double[size - 1];
        for (int j = 0; j < size - 1; j++)
            f[i][j] = 0;
    }
    get_f(f, x, y, size);
    for (int i = 0; i < size - 1; i++) {
        double temp = f[i][0];
        for (int j = 0; j < i + 1; j++)
            temp *= (X - x[j]);
        result += temp;
    }
    return result;
}
double Eitken(double X, double* x, double* y, int size)
{
    double P[size][size] = { 0 };
    for (int j = 0; j < size; j++) {
        P[j][j] = y[j];
        for (int i = j - 1; i >= 0; i--)
            P[i][j] = 1 / (x[j] - x[i]) * ((X - x[i]) * P[i + 1][j] - (X - x[j]) * P[i][j - 1]);
    }
    // cout << endl;
    // for (int k = 0; k < size; k++) {
    //     for (int l = 0; l < size; l++) {
    //         cout << P[k][l] << " ";
    //     }
    //     cout << endl;
    // }
    return P[0][size - 1];
}

void progon(double* a, double* b, double* c, double* d, double* X, int N)
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
    x[0] = x[N - 1] = 0;

    // Вывод ответа
    for (int i = 0; i < N; i++) {
        X[i] = x[i];
        // cout << "X[" << i + 1 << "] = " << round(x[i] * 100) / 100 << " ";
    }
    // cout << endl;
}

double cube_splain_v2(double X, double* x, double* y, int size)
{
    int sect = size - 1;

    double a[sect];
    double b[size];
    double c[sect];
    double d[size];
    c[0] = 0;
    for (int i = 0; i < sect; i++) {
        a[i] = y[i];
    }
    double* alpha = new double[sect];
    double* beta = new double[sect];
    double C, F, h, h1, z;
    alpha[0] = beta[0] = 0.0;
    for (int i = 1; i < sect; ++i) {
        h = x[i] - x[i - 1], h1 = x[i + 1] - x[i];
        C = 2.0 * (h + h1);
        F = 6.0 * ((y[i + 1] - y[i]) / h1 - (y[i] - y[i - 1]) / h);
        z = (h * alpha[i - 1] + C);
        alpha[i] = -h1 / z;
        beta[i] = (F - h * beta[i - 1]) / z;
    }
    c[sect - 1] = (F - h * beta[sect - 2]) / (C + h * alpha[sect - 2]);
    for (int i = sect - 2; i > 0; --i)
        c[i] = alpha[i] * c[i + 1] + beta[i];
    for (int i = sect - 1; i > 0; --i) {
        h = x[i] - x[i - 1];
        d[i] = (c[i] - c[i - 1]) / h;
        b[i] = h * (2.0 * c[i] + c[i - 1]) / 6.0 + (y[i] - y[i - 1]) / h;
    }
    int i = 0;
    if (X <= x[0]) {
        i = 1;
    } else if (X >= x[size - 1]) {
        i = size - 1;
    } else {
        while (X >= x[i] && i != size) {
            i++;
        }
        i--;
    }
    double dx = (X - x[i]);
    return a[i] + (b[i] + (c[i] / 2.0 + d[i] * dx / 6.0) * dx) * dx;
}

double cube_splain(double X, double* x, double* y, int size)
{
    double M[size];

    double a[size - 1];
    double b[size];
    double c[size - 1];
    double d[size];

    double h[size];

    for (int i = 1; i < size; i++) {
        h[i] = x[i] - x[i - 1];
    }
    for (int i = 0; i < size; i++) {
        if (i != 0) {
            a[i] = h[i - 1] / 6;
        }
        if (i != size - 1) {
            c[i] = h[i + 1] / 6;
        }
        if (i != 0 && i != size - 1) {
            d[i] = (y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i];
        }
        b[i] = (h[i] + h[i + 1]) / 3;
    }
    // cout << endl;
    // for (int i = 0; i < size; i++) {
    //     if (i != 0) {
    //         cout << std::setw(15) << std::left << a[i];
    //     }
    //     if (i != size - 1) {
    //         cout << std::setw(15) << std::left << c[i];
    //     }
    //     if (i != 0 && i != size - 1) {
    //         cout << std::setw(15) << std::left << d[i];
    //     }
    //     cout << std::setw(15) << std::left << b[i];
    // }
    progon(a, b, c, d, M, size);
    int i = 0;
    while (i != size && X >= x[i]) {
        i++;
    }
    double res = M[i - 1] * (x[i] - X) * (x[i] - X) * (x[i] - X) / (6 * h[i]);
    res += M[i] * (X - x[i - 1]) * (X - x[i - 1]) * (X - x[i - 1]) / (6 * h[i]);
    res += (y[i - 1] - (M[i - 1] * h[i] * h[i]) / 6) * ((x[i] - X) / h[i]);
    res += (y[i] - (M[i] * h[i] * h[i]) / 6) * ((X - x[i - 1]) / h[i]);
    return res;
}
int main()
{
    int size;
    char ans = 'n';
    double X;
    double* x;
    double* y;
    cout << "Do you wanna use template: ";
    cin >> ans;
    if (ans == 'y') {
        size = 3;
        x = new double[size], y = new double[size];
        x[0] = 100.0, x[1] = 121.0, x[2] = 144.0;
        y[0] = 10.0, y[1] = 11.0, y[2] = 12.0;
        // x[0] = 1.0, x[1] = 1.1, x[2] = 1.3, x[3] = 1.5, x[4] = 1.6;
        // y[0] = 1.0, y[1] = 1.032, y[2] = 1.091, y[3] = 1.145, y[4] = 1.17;
        X = 115;
    } else {
        cout << "Do you wanna use func: ";
        cin >> ans;
        if (ans == 'y') {
            cout << "size = ";
            cin >> size;
            x = new double[size];
            y = new double[size];
            for (int i = 0; i < size; i++) {
                x[i] = i;
                y[i] = func(i);
            }
            cout << "X = ";
            cin >> X;
        } else {
            cout << "size = ";
            cin >> size;
            x = new double[size];
            y = new double[size];
            for (int i = 0; i < size; i++) {
                cout << "x[" << i + 1 << "]= ";
                cin >> x[i];
            }
            for (int i = 0; i < size; i++) {
                cout << "y[" << i + 1 << "]= ";
                cin >> y[i];
            }
            cout << "X = ";
            cin >> X;
        }
    }
    cout << "Lagrange result: " << Lagrange(X, x, y, size) << endl;
    double res = Niuton(X, x, y, size);
    cout << "Niuton result: " << res << endl;
    cout << "Aitken result: " << Eitken(X, x, y, size) << endl;
    cout << "Cube splain result: " << cube_splain(X, x, y, size) << endl;
    cout << "Cube splain v1.2 result: " << cube_splain_v2(X, x, y, size) << endl;
    return 0;
}