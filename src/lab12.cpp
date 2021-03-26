#include <iostream>
#include <stdlib.h>

using namespace std;

void setrand(double *x, double *y, int n) {
  double a = (rand() % 100) * 0.05;
  double b = (rand() % 100) * 0.05;
  for (int i = 0; i<n; i++) {
    x[i] = (double)i;
    y[i] = a * (double)i + b;
  }
}

void approx(double *x, double *y, int n) {
  double sumx, sumy, sumx2, sumxy;
  sumx = sumy = sumx2 = sumxy = 0;
  for (int i = 0; i < n; i++) {
    sumx += x[i], sumy += y[i];
    sumx2 += x[i] * x[i];
    sumxy += x[i] * y[i];
  }
  double delta = sumx2 * n - sumx * sumx;
  if (delta != 0) {
    cout << "Система имеет единственное решение" << endl;
    double a = (sumxy * n - sumy * sumx) / delta;
    double b = (sumx2 * sumy - sumx * sumxy) / delta;
    cout << "Formula: y = ax + b\na = " <<  a << "\nb = " << b << endl;
  }
}

int main() {
  double *x, *y;
  int n = 5, ans = 0;
  cout << "How you wanna input values:\n1) Use template\n2) Enter by myself\n3) Random values\n";
  cin >> ans;
  if (ans > 1) {
    cout << "n = ";
    cin >> n;
  }
  x = new double[n];
  y = new double[n];
  if (ans == 2) {
    for (int i = 0; i < n; i++) {
      cout << "x[" << i + 1 << "] = ";
      cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
      cout << "y[" << i + 1 << "] = ";
      cin >> y[i];
    }
  } else if (ans == 3) {
    setrand(x, y, n);
    for (int i = 0; i < n; i++)
      cout << x[i] << " " << y[i] << endl;
  } else {
    x = new double[n];
    y = new double[n];
    for (int i = 0; i < n; i++) {
      x[i] = (double)i;
    }
    for (int i = 0; i < n; i++) {
      y[i] = 65 * (double)i;
    }
    for (int i = 0; i < n; i++)
      cout << x[i] << " " << y[i] << endl;
  }
  approx(x, y, n);
  delete x;
  delete y;
  return 0;
}