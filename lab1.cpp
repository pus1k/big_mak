#include <cmath>
#include <float.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Matrix {
    int n, m;
    double** a;
};
typedef Matrix Matrix;

Matrix* new_matrix(int a, int b)
{
    Matrix* mat = new Matrix;
    mat->n = a;
    mat->m = b;
    mat->a = new double*[mat->n];
    for (int i = 0; i < mat->n; i++) {
        mat->a[i] = new double[mat->m];
    }
    return mat;
}

int max(const int a, const int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void output(Matrix* mat, double* x)
{
    for (int l = 0; l < mat->n; l++) {
        for (int e = 0; e < mat->m; e++) {
            cout << mat->a[l][e] << " ";
        }
        cout << x[l] << endl;
    }
    cout << endl;
}

int is_zero_raw(Matrix* mat, double* x, int k)
{
    int i;
    for (i = 0; i < mat->n; i++) {
        if (mat->a[k][i] != 0) {
            break;
        }
    }
    if (i == mat->n) {
        x[k] = 0;
        return 1;
    } else {
        return 0;
    }
}

int get_rank(Matrix* mat)
{
    const double EPS = 1E-9;
    Matrix* temp = new_matrix(mat->n, mat->m);
    for (int i = 0; i < temp->n; i++) {
        for (int j = 0; j < temp->m; j++) {
            temp->a[i][j] = mat->a[i][j];
        }
    }
    int rank = max(temp->n, temp->m);
    vector<char> line_used(temp->n);
    for (int i = 0; i < temp->m; ++i) {
        int j;
        for (j = 0; j < temp->n; ++j)
            if (!line_used[j] && abs(temp->a[j][i]) > EPS)
                break;
        if (j == temp->n)
            --rank;
        else {
            line_used[j] = true;
            for (int p = i + 1; p < temp->m; ++p)
                temp->a[j][p] /= temp->a[j][i];
            for (int k = 0; k < temp->n; ++k)
                if (k != j && abs(temp->a[k][i]) > EPS)
                    for (int p = i + 1; p < temp->m; ++p)
                        temp->a[k][p] -= temp->a[j][p] * temp->a[k][i];
        }
    }
    return rank;
}
void swap(Matrix* mat, double* x, int k)
{
    double temp;
    for (int i = 0; i < mat->n; i++) {
        if (mat->a[i][k] != 0) {
            for (int j = 0; j < mat->m; j++) {
                temp = mat->a[k][j];
                mat->a[k][j] = mat->a[i][j];
                mat->a[i][j] = temp;
            }
            temp = x[k];
            x[k] = x[i];
            x[i] = temp;
        }
    }
}
void gauss(Matrix* mat, double* x)
{
    int i, j, k;
    double c;
    Matrix* mat_plus = new_matrix(mat->n, mat->m + 1);
    for (i = 0; i < mat->n; i++) {
        for (j = 0; j < mat->m; j++) {
            mat_plus->a[i][j] = mat->a[i][j];
        }
        mat_plus->a[i][j] = x[i];
    }
    if (get_rank(mat) == get_rank(mat_plus)) {
        for (k = 0; k < mat->n; k++) {
            if (mat->a[k][k] == 0) {
                swap(mat, x, k);
            }
            if (mat->a[k][k] != 0) {
                c = 1 / mat->a[k][k];
                for (i = k; i < mat->m; i++) {
                    mat->a[k][i] *= c;
                }
                x[k] *= c;
                for (i = k + 1; i < mat->n; i++) {
                    if (is_zero_raw(mat, x, i) == 0) {
                        for (j = k + 1; j < mat->m; j++) {
                            mat->a[i][j] -= mat->a[i][k] * mat->a[k][j];
                        }
                        x[i] -= mat->a[i][k] * x[k];
                        mat->a[i][k] = 0;
                    }
                }
                output(mat, x);
            }
        }
        for (i = mat->n - 2; i >= 0; i--) {
            for (j = i + 1; j < mat->m; j++) {
                x[i] -= mat->a[i][j] * x[j];
            }
        }
        for (i = 0; i < mat->n; i++) {
            for (j = 0; j < mat->m; j++) {
                if (is_zero_raw(mat, x, i) == 1 && x[i] == 0) {
                    x[i] = DBL_MAX;
                }
            }
        }
    } else {
        cout << "Your matrix not correct!" << endl;
        return;
    }
}

void gauss_jordan(Matrix* mat, double* x)
{
    int i, j, i_target = 0;
    double c;
    for (i = 0; i < mat->n; i++) {
        output(mat, x);
        c = 1 / mat->a[i_target][i];
        for (j = i; j < mat->n; j++) {
            mat->a[i_target][j] *= c;
        }
        x[i_target] *= c;
        for (j = 0; j < mat->n; j++) {
            if (j != i_target) {
                x[j] -= mat->a[j][i] * x[i_target];
                for (int l = mat->n - 1; l >= i; l--) {
                    mat->a[j][l] -= mat->a[j][i] * mat->a[i_target][l];
                }
            }
        }
        i_target++;
    }
    output(mat, x);
}

int main()
{
    Matrix* mat = new_matrix(3, 3);
    double x[mat->n];
    mat->a[0][0] = 0, mat->a[0][1] = 1, mat->a[0][2] = 0;
    mat->a[1][0] = 0, mat->a[1][1] = 0, mat->a[1][2] = 0;
    mat->a[2][0] = 0, mat->a[2][1] = 0, mat->a[2][2] = 0;
    x[0] = 1, x[1] = 0, x[2] = 0;

    output(mat, x);
    // gauss_jordan(mat, x);
    gauss(mat, x);
    for (int i = 0; i < mat->n; i++) {
        if (x[i] != DBL_MAX)
            cout << "x" << i + 1 << " " << x[i] << endl;
    }
    cout << endl;
}