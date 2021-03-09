#include <chrono>
#include <cmath>
#include <float.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

#define N 3

int max(const int a, const int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void Output(double** a)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void Swap(double** a, int k)
{
    double temp;
    for (int i = 0; i < N; i++) {
        if (a[i][k] != 0) {
            for (int j = 0; j <= N; j++) {
                temp = a[k][j];
                a[k][j] = a[i][j];
                a[i][j] = temp;
            }
            return;
        }
    }
}
int Zero_Raw(double** a, int k)
{
    int j = 0;
    while ((j < N) && (a[k][j] == 0)) {
        j++;
    }
    if (j == N) {
        return 1;
    }
    return 0;
}
int Zero_Col(double** a, int k)
{
    int i = 0;
    while (i < N && a[i][k] == 0) {
        i++;
    }
    if (i == N) {
        return 1;
    }
    return 0;
}
int Inf_Solution(double** a)
{
    int i;
    for (i = 0; i < N; ++i) {
        if (Zero_Raw(a, i) == 1) {
            if (a[i][N] == 0) {
                if (Zero_Col(a, i) == 0) {
                    return 1;
                }
            } else {
                return 2;
            }
        }
    }
    return 0;
}
void Gauss_Jordan(double** a)
{
    int i, j, k;
    double c;
    for (i = 0; i < N; i++) {
        if (a[i][i] == 0) {
            Swap(a, i);
        }
    }
    if (Inf_Solution(a) == 1) {
        cout << "inf sol" << endl;
        return;
    } else if (Inf_Solution(a) == 2) {
        cout << "no sol" << endl;
        return;
    }
    for (k = 0; k < N; k++) {
        int i_max = k;
        double a_max = fabs(a[k][k]);
        for (i = k + 1; i < N; i++) {
            if (fabs(a[i][k]) > a_max) {
                a_max = fabs(a[i][k]);
                i_max = i;
            }
        }
        if (k != i_max) {
            for (j = k; j <= N; j++) {
                c = a[k][j];
                a[k][j] = a[i_max][j];
                a[i_max][j] = c;
            }
        }
        if (Inf_Solution(a) == 1) {
            cout << "inf sol" << endl;
            return;
        } else if (Inf_Solution(a) == 2) {
            cout << "no sol" << endl;
            return;
        }
        if (a[k][k] != 0) {
            c = 1 / a[k][k];
            for (j = k; j <= N; j++) {
                a[k][j] *= c;
            }
            for (i = 0; i < N; i++) {
                if (i != k) {
                    for (j = N; j >= k; j--) {
                        a[i][j] -= a[i][k] * a[k][j];
                        if (fabs(a[i][N]) < 1E-10) {
                            a[i][N] = 0;
                        }
                    }
                }
            }
        }
        Output(a);
    }
    if (Inf_Solution(a) == 1) {
        cout << "inf sol" << endl;
        return;
    } else if (Inf_Solution(a) == 2) {
        cout << "no sol" << endl;
        return;
    }
    cout << endl;
    for (i = 0; i < N; i++) {
        if (Zero_Col(a, i) == 0) {
            cout << "X" << i + 1 << " = " << a[i][N] << endl;
        }
    }
}

int main()
{
    int ent;
    cout << "Как вы хотите ввести матрицу:\n1. Рандомно\n2. С клавиатуры" << endl;
    cin >> ent;

    srand(time(NULL));

    double** a = new double*[N];

    if (ent == 1) {
        for (int i = 0; i < N; i++) {
            a[i] = new double[N + 1];
            for (int j = 0; j < N + 1; j++) {
                a[i][j] = rand() % 2 - 0;
            }
        }
    } else if (ent == 2) {
        for (int i = 0; i < N; i++) {
            a[i] = new double[N + 1];
            for (int j = 0; j < N + 1; j++) {
                cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
                cin >> a[i][j];
            }
        }
    } else {
        cout << "Ошибка!" << endl;
    }
    cout << endl;
    Output(a);
    Gauss_Jordan(a);
    return 0;
}