#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

double fun(double x)
{
    // x = 1,875
    return cos(2 / x) - 2 * sin(1 / x) + 1 / x;
    // x = 1,2442
    // return -1 * (x * x * x) - 2 * (x * x) - 4 * x + 10;
}
double p1fun(double x)
{
    return (2 * sin(2 / x) / (x * x)) + (2 * cos(1 / x) / (x * x)) - 1 / (x * x);
    // return -3 * x * x - 4 * x - 4;
}
double p2fun(double x)
{
    return 2 / (x * x * x) - (4 * sin(2 / x) / (x * x * x)) - (4 * cos(2 / x) / (x * x * x * x)) - (4 * cos(1 / x) / (x * x * x)) + (2 * sin(1 / x) / (x * x * x * x));
    // return -6 * x - 4;
}
void bisec(double begin, double end, double e)
{
    if (fun(begin) * fun(end) < 0) {
        cout << "Условие на сходимость выполняется!" << endl;
        double c = (end + begin) / 2;
        double a = begin, b = end;
        int i = 1;
        cout << std::setw(15) << std::left << "i" << std::setw(15) << "a" << std::setw(15) << "b" << std::setw(15) << "x" << std::setw(15) << "f(a)" << std::setw(15) << "f(x)" << endl;
        while (fabs(fun(c)) > e) {
            c = (b + a) / 2;
            if (fun(a) * fun(c) < 0) {
                b = c;
            } else {
                a = c;
            }
            cout << std::setw(15) << std::left << i << std::setw(15) << a << std::setw(15) << b << std::setw(15) << c << std::setw(15) << fun(a) << std::setw(15) << fun(c) << endl;
            i++;
        }
    } else {
        cout << "Условие на сходимость не выполняется!" << endl;
    }
}
void niut(double a, double b, double e)
{
    int iter = 1;
    double x;
    int flag = 0;
    if (fun(a) * p2fun(a) > 0) {
        cout << "Условие на сходимость выполняется для а!" << endl;
        flag = 1, x = a;
    } else if (fun(b) * p2fun(b) > 0) {
        cout << "Условие на сходимость выполняется для b!" << endl;
        flag = 1, x = b;
    }
    if (flag) {
        cout << std::setw(15) << std::left << "i" << std::setw(15) << "x" << std::setw(15) << "f(x)" << std::setw(15) << "f'(x)" << endl;
        while (fabs(fun(x)) > e) {
            x -= fun(x) / p1fun(x);
            cout << std::setw(15) << std::left << iter << std::setw(15) << x << std::setw(15) << fun(x) << std::setw(15) << p1fun(x) << endl;
            iter++;
        }
    }
}
void hord(double a, double b, double e)
{
    int iter = 1;
    double x, pastx, temp;
    int flag = 0;
    if (fun(a) * p2fun(a) > 0) {
        cout << "Условие на сходимость выполняется для а!" << endl;
        flag = 1;
    } else if (fun(b) * p2fun(b) > 0) {
        cout << "Условие на сходимость выполняется для b!" << endl;
        flag = 1;
    }
    if (flag) {
        x = b, pastx = a;
        cout << std::setw(15) << std::left << "i" << std::setw(15) << "x" << std::setw(15) << "px" << std::setw(15) << "f(x)" << std::setw(15) << "f(px)" << endl;
        while (fabs(x - pastx) > e) {
            temp = x;
            x -= fun(x) * ((x - pastx) / (fun(x) - fun(pastx)));
            pastx = temp;
            cout << std::setw(15) << std::left << iter << std::setw(15) << x << std::setw(15) << pastx << std::setw(15) << fun(x) << std::setw(15) << fun(pastx) << endl;
            iter++;
        }
    }
}

int main()
{
    double e, begin, end;
    std::cout << "Do you wanna fill your matrix by yourself:" << std::endl;
    std::cout << "1) Yes" << std::endl;
    std::cout << "2) Use template" << std::endl;
    std::cin >> e;
    if (e == 1) {
        cout << "a = ";
        cin >> begin;
        cout << "b = ";
        cin >> end;
        cout << "e = ";
        cin >> e;
    } else {
        begin = 1.8, end = 2, e = 0.001;
        // begin = 0, end = 2, e = 0.01;
    }
    bisec(begin, end, e);
    cout << endl;
    niut(begin, end, e);
    cout << endl;
    hord(begin, end, e);
    return 0;
}