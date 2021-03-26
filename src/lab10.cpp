#include <iostream>
#include <cmath>

using namespace std;

double func (double x)
{
  return 3*x*x;
}
double integr(double a, double b, int n)
{
  double h = (b - a) / n;
  double* x = new double[n];
  double I1 = 0;
  x[0] = a, x[n - 1] = b;
  for (int i = 1; i < n - 1; i++)
    x[i] = x[i - 1] + h;
  for (int i = 0; i < n; i++) {
    if (i == 0 || i == n - 1) {
      I1 += 0.5 * func(x[i]);
    } else {
      I1 += func(x[i]);
    }
  }
  I1 *= h;
  delete(x);
  return I1;
}
void gauss(double a, double b)
{
  double rez = (b - a) / 2 * func((a + b) / 2 - (b - a) / (2 * sqrt(3)));
  rez += (b - a) / 2 * func((a + b) / 2 + (b - a) / (2 * sqrt(3)));
  cout << "Gauss rezult: " << rez << endl;
}
void exe(double a, double b, int n, double e)
{
  double I1 = integr(a, b, n);
  double I2 = integr(a, b, n * 2);
  int i = 2;
  while (abs(I2 - I1) > e) {
    I1 = I2, i *= 2;
    I2 = integr(a, b, n * i);
  }
  cout << "Runge rezult: " << I2 << endl;
  gauss(a, b);
}

int main ()
{
  int n = 1000, ans = 0;
  double a = 0;
  double b = 5;
  double e = 0.1;
  cout << "How you wanna input values:\n1) Use template\n2) Enter by myself\n";
  cin >> ans;
  if (ans == 2) {
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "n = ";
    cin >> n;
    cout << "e = ";
    cin >> e;
  } else {
  cout << "a = " << a << ", b = " << b << ", n = " << n << ", e = " << e << endl;    
  }
  exe(a, b, n, e);
  return 0;
}