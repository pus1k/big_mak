#include <iostream>
#include <cmath>

using namespace std;

double func (double x, double y)
{
  return x * x - 2 * y;
}
void eiler(double a, double b, double y0, int n)
{
  double* x = new double[n];
  x[0] = a;
  for (int i = 1; i < n; i++) {
    x[i] = x[i - 1] + (b - a) / n;
  }
  double h = (b - a) / n;
  double y[n];
  y[0] = y0;
  for (int i = 1; i < n; i++) {
    y[i] = y[i - 1] + h * func(x[i - 1], y[i - 1]);
  }
  h = y[n - 1] + h * func(x[n-1], y[n - 1]);
  cout << "Eirler rezult: " << h << endl;
}
double runge_iav(double a, double b, double y0, int n)
{
  double* x = new double[n];
  double h = (b - a) / n;
  double y[n];
  double k;
  y[0] = y0;
  x[0] = a;
  for (int i = 1; i < n; i++) {
    x[i] = x[i - 1] + h;
  }
  for (int i = 1; i < n; i++) {
    y[i] = y[i - 1];
    k = func(x[i - 1], y[i - 1]);
    y[i] += h * k / 6;
    k = func((x[i - 1] + (h / 2)), (y[i - 1] + (h * k / 2)));
    y[i] += h * k / 3;
    k = func((x[i - 1] + (h / 2)), (y[i - 1] + (h * k / 2)));
    y[i] += h * k / 3;
    k = func((x[i - 1] + h), (y[i - 1] + h * k));
    y[i] += h * k / 6;
  }
  // for (int i = 0; i < n; i++) {
  //   cout << x[i] << " " << y[i] << " " << func(x[i], y[i]) << endl;
  // }
  // cout << endl;
  double temp = y[n - 1];
  k = func(x[n - 1], y[n - 1]);
  temp += h * k / 6;
  k = func((x[n - 1] + (h / 2)), (y[n - 1] + (h * k / 2)));
  temp+= h * k / 3;
  k = func((x[n - 1] + (h / 2)), (y[n - 1] + (h * k / 2)));
  temp += h * k / 3;
  k = func((x[n - 1] + h), (y[n - 1] + h * k));
  temp += h * k / 6;
  return temp;
}
double runge(double a, double b, double y0, int n)
{
  double* x = new double[n];
  double h = (b - a) / n;
  double y[n];
  double k;
  y[0] = y0;
  x[0] = a;
  for (int i = 1; i < n; i++) {
    x[i] = x[i - 1] + h;
  }
  for (int i = 1; i < n; i++) {
    k = y[i - 1] + h * func(x[i - 1], y[i - 1]) / 2;
    y[i] = y[i - 1] + h * (func(x[i - 1], y[i - 1]) + func(x[i - 1] + h, k)) / 2;
  }
  // for (int i = 0; i < n; i++) {
  //   cout << x[i] << " " << y[i] << endl;
  // }
  // cout << x[n] << endl;
  k = y[n - 1] + h * func(x[n - 1], y[n - 1]) / 2;
  k = y[n - 1] + h * (func(x[n - 1], y[n - 1]) + func(x[n - 1] + h, k)) / 2;
  return k;
}
void exe(double a, double b, double y0, int n, double e)
{
  double DF1 = runge(a, b, y0, n);
  double DF2 = runge(a, b, y0, n * 2);
  int i = 2;
  while (abs(DF2 - DF1) > e) {
    DF1 = DF2, i *= 2;
    DF2 = runge(a, b, y0, n * i);
  }
  cout << "Runge rezult: " << DF1 << endl;
  eiler(a, b, y0, n);
}

int main ()
{
  int n = 1000, ans = 0;
  double a = 0;
  double b = 1;
  double e = 0.001;
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
    cout << "y0 = ";
    cin >> ans;
  } else {
  cout << "a = " << a << ", b = " << b << ", n = " << n << ", e = " << e << endl;    
  }
  exe(a, b, ans, n, e);
  return 0;
}