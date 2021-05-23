// sudo apt-get gnuplot
// sudo apt-get install fim

#include <cmath>
#include <fstream>
#include <iostream>
#include <unistd.h>

#define eps 0.001
#define N 5

using std::cout;
using std::endl;

double a = 0, b = 1;
double h = (b - a) / N;
double Ya = 2, Yb = 3;
double X[N];
double Y[N];
double Z[N];

double dif(double x, double y, double d1)
{
    return 3 * x + 4 * sin(x) * d1 - ((9 * y) / pow((x + 4), 2));
}
void rynge_kytt()
{
    for (int i = 0; i < N; i++) {
        Y[i] = 0, X[i] = X[i - 1] + h, Z[i] = 0;
    }
    double ky[4], kz[4];
    while (fabs(Yb - Y[N - 1]) > eps) {
        Y[0] = Ya, X[0] = 0, Z[0] += eps;
        for (int i = 1; i < N; i++) {
            Y[i] = Y[i - 1], Z[i] = Z[i - 1];
            kz[0] = dif(X[i - 1], Y[i - 1], Z[i - 1]);
            ky[0] = Z[i - 1];
            Y[i] += h * ky[0] / 6, Z[i] += h * kz[0] / 6;

            kz[1] = dif(X[i - 1] + h / 2, Y[i - 1] + h * ky[0] / 2, Z[i - 1] + h * kz[0] / 2);
            ky[1] = Z[i - 1] + kz[0] * h / 2;
            Y[i] += h * ky[1] / 3, Z[i] += h * kz[1] / 3;

            kz[2] = dif(X[i - 1] + h / 2, Y[i - 1] + h * ky[1] / 2, Z[i - 1] + h * kz[1] / 2);
            ky[2] = Z[i - 1] + kz[1] * h / 2;
            Y[i] += h * ky[2] / 3, Z[i] += h * kz[2] / 3;

            kz[3] = dif(X[i - 1] + h, Y[i - 1] + h * ky[2], Z[i - 1] + h * kz[2]);
            ky[3] = Z[i - 1] + kz[2] * h;
            Y[i] += h * ky[3] / 6, Z[i] += h * kz[3] / 6;
        }
    }
    cout << "X[i]\tY[i]\tZ[i]" << endl;
    for (int i = 0; i < N; i++) {
        cout << X[i] << "\t" << Y[i] << "\t" << Z[i] << endl;
    }
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
double Lagrange_for_graph(double X, double* x, int size, int i)
{
    double result = 1;
    for (int j = 0; j < size; j++) {
        if (j != i) { // условие для исключения появления 0 в знаменателе
            result *= (X - x[j]) / (x[i] - x[j]);
        }
    }
    return result * Y[4];
}
double Simpson(double ya, double yb, double mid)
{
    return (b - a) / 6 * (ya + 4 * mid + yb);
}
void draw()
{
    std::ofstream yfile("y.txt", std::ios::binary);
    std::ofstream intfile("int.txt", std::ios::binary);
    if (yfile.is_open() && intfile.is_open()) {
        for (int i = 0; i < N; i++) {
            yfile << X[i] << " " << Y[i] << endl;
            intfile << X[i] << " " << Lagrange_for_graph(X[i], X, N, 4) << endl;
        }
        std::system("gnuplot src/kurs.p");
        yfile.close();
        intfile.close();
        std::system("fim -a kurs.png");
    }
}
int main()
{
    rynge_kytt();
    double mid = (Z[1] + Z[2]) / 2;
    cout << "Interpolation: " << Lagrange(0.5, X, Y, N) << endl;
    cout << "Integral: " << Simpson(Z[0], Z[N - 1], mid) << endl;
    draw();
    return 0;
}