#include <cmath>
#include <iostream>

int check_for_coverege(double** a, int n)
{
    int s[n] = { 0 };
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < n; j++) {
            if (j != i)
                sum += fabs(a[i][j]);
        }
        if (fabs(a[i][i]) > sum)
            s[i] = 1;
        else
            s[i] = 0;
    }
    sum = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 1) {
            sum++;
        }
    }
    if (sum == n) {
        return 0;
    } else {
        return 1;
    }
}
int check_for_accuracy(double* xx, double* x, int n, double e)
{
    int s[n] = { 0 };
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(xx[i] - x[i]) < e)
            s[i] = 1;
        else
            s[i] = 0;
    }
    sum = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 1) {
            sum++;
        }
    }
    return sum;
}
void simp_iter(double** a, double* b, int n, double e)
{
    int sum = 0;
    if (!check_for_coverege(a, n)) {
        double x[n] = { 0.0 };
        double xx[n] = { 0.0 };
        int k = 0;
        sum = 0;
        while (sum != n) {
            ////////ITERATION////////
            for (int i = 0; i < n; i++) {
                xx[i] = x[i];
            }
            for (int i = 0; i < n; i++) {
                x[i] = b[i];
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        x[i] -= a[i][j] * xx[j];
                    }
                }
                x[i] /= a[i][i];
                std::cout << "X" << i + 1 << " = " << round(x[i] * 1000) / 1000 << "\t";
            }
            std::cout << std::endl;
            k += 1;
            sum = check_for_accuracy(xx, x, n, e);
            /////////////////////////
        }
        //////////OUTPUT ANSWER//////////
        std::cout << "Answer:" << std::endl;
        std::cout << "    K = " << k << std::endl;
        std::cout << "    e = " << e << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "    X" << i + 1 << " = " << round(x[i] * 1000) / 1000 << std::endl;
        }
    } else {
        std::cout << "The system does't coverege." << std::endl;
    }
}
void zeidel_iter(double** a, double* b, int n, double e)
{
    int sum = 0;
    if (!check_for_coverege(a, n)) {
        double x[n] = { 0.0 };
        double xx[n] = { 0.0 };
        int k = 0;
        sum = 0;
        while (sum != n) {
            ////////ITERATION////////
            for (int i = 0; i < n; i++) {
                xx[i] = x[i];
            }
            for (int i = 0; i < n; i++) {
                x[i] = b[i];
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        if (j < i) {
                            x[i] -= a[i][j] * x[j];
                        } else {
                            x[i] -= a[i][j] * xx[j];
                        }
                    }
                }
                x[i] /= a[i][i];
                std::cout << "X" << i + 1 << " = " << round(x[i] * 1000) / 1000 << "\t";
            }
            std::cout << std::endl;
            k += 1;
            sum = check_for_accuracy(xx, x, n, e);
            /////////////////////////
        }
        //////////OUTPUT ANSWER//////////
        std::cout << "Answer:" << std::endl;
        std::cout << "    K = " << k << std::endl;
        std::cout << "    e = " << e << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "    X" << i + 1 << " = " << round(x[i] * 1000) / 1000 << std::endl;
        }
    } else {
        std::cout << "The system does't coverege." << std::endl;
    }
}
int main()
{
    int n = 4;
    int ans = 0;
    double e;
    double b[n];
    double** a;
    std::cout << "Do you wanna fill your matrix by yourself:" << std::endl;
    std::cout << "1) Yes" << std::endl;
    std::cout << "2) Use template" << std::endl;
    std::cin >> ans;
    if (ans == 2) {
        a = new double*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[n];
        }
        a[0][0] = 20, a[0][1] = 2, a[0][2] = 3, a[0][3] = 7;
        a[1][0] = 1, a[1][1] = 12, a[1][2] = -2, a[1][3] = -5;
        a[2][0] = 5, a[2][1] = -3, a[2][2] = 13, a[2][3] = 0;
        a[3][0] = 0, a[3][1] = 0, a[3][2] = -1, a[3][3] = 15;
        b[0] = 5, b[1] = 4, b[2] = -3, b[3] = 7;
        e = 0.1;
    } else {
        std::cout << "n = ";
        std::cin >> n;
        a = new double*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[n];
            for (int j = 0; j < n; j++) {
                std::cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
                std::cin >> a[i][j];
            }
            std::cout << "b[" << i + 1 << "] = ";
            std::cin >> b[i];
        }
        std::cout << "e = ";
        std::cin >> e;
    }
    simp_iter(a, b, n, e);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    zeidel_iter(a, b, n, e);
    // Answer 0,083
    // 		  0,472
    // 		 -0,156
    // 		  0,45
}