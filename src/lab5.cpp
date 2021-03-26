#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int n = 3;

double sec_opred(double* a)
{
  return a[0] * a[3] - a[2] * a[1];
}
double third_opred(double** a)
{
  return a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1] - a[0][2] * a[1][1] * a[2][0] - a[0][0] * a[1][2] * a[2][1] - a[0][1] * a[1][0] * a[2][2];
}
double func (int i, double* x)
{
  if (i == 1)
    return x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 1;
  if (i == 2)
    return 2 * x[0] * x[0] + x[1] * x[1] - 4 * x[2];
  if (i == 3)
    return 3 * x[0] * x[0] - 4 * x[1] + x[2] * x[2];
  return 0;
}
void dgemm(double **a, double *b, double *c, int n)
{
  for (int i = 0; i < n; i++) {
    c[i] = 0;
    for (int j = 0; j < n; j++) {
      c[i] += a[i][j] * b[j];
    }
  }
}
int geta(double **a, double *b, int n)
{
  double **nea = new double*[n];
  for (int i = 0; i < n; i++) {
    nea[i] = new double[n];
  }
  a[0][0] = 2 * b[0], a[0][1] = 2 * b[0], a[0][2] = 2 * b[0];
  a[1][0] = 4 * b[1], a[1][1] = 2 * b[1], a[1][2] = -4;
  a[2][0] = 6 * b[2], a[2][1] = -4, a[2][2] = 2 * b[2];
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < n; j++) {
  //     cout << a[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
  double delta = third_opred(a);
  if (delta != 0) {
    double temp[4];
    int num = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          for (int l = 0; l < n; l++) {
            if (k != i && l != j) {
              temp[num] = a[k][l], num++;
            }
          }
        }
        num = 0;
        nea[i][j] = sec_opred(temp);
      }
    }
    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < n; j++) {
    //     cout << nea[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    double tmp = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (i != j) {
          tmp = nea[i][j];
          nea[i][j] = nea[j][i];
          nea[j][i] = tmp;
        }
      }
    }
    // cout << endl;
    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < n; j++) {
    //     cout << nea[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;
    nea[0][1] *= -1, nea[1][0] *= -1, nea[1][2] *= -1, nea[2][1] *= -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        a[i][j] = nea[i][j] / delta;
      }
    }
    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < n; j++) {
    //     cout << a[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    return 1;
  }
  return 0;
}
void niut(double* X0, double e)
{
  double present[n];
  double past[n];
  for (int i = 0; i < n; i++) {
    present[i] = X0[i];
    past[i] = present[i];
  }
  double F[n];
  double **a = new double*[n];
  double *c = new double[n];
  for (int i = 0; i < n; i++) {
    a[i] = new double[n];
    for (int j = 0; j < n; j++) {
      a[i][j] = 0;
    }
  }
  int flag = 1;
  do {
    for (int i = 0; i < n; i++) {
      past[i] = present[i];
      F[i] = func(i + 1, past);
    }
    if (geta(a, past, n)) {
      dgemm(a, F, c, n);
      // for (int i = 0; i < n; i++) {
      //   cout << c[i] << endl;
      // }
      // cout << endl;
      for (int i = 0; i < n; i++)
        present[i] = past[i] - c[i];
      flag = 0;
      while (present[flag] - past[flag] <= e && flag != n) {
        flag++;
      }
      if (flag == n) {
        flag = 0;
      } else {
        flag = 1;
      }
    } else {
      cout << "Error" << endl;
      return;
    }
  } while(flag);
  cout << endl;
  for (int i = 0; i < n; i++) {
    cout << present[i] << endl;
  }
}
int main()
{
  double X0[n];
  double e = 0;
  std::cout << "How you wanna enter x:" << std::endl;
  std::cout << "1) By my self" << std::endl;
  std::cout << "2) Use template" << std::endl;
  std::cin >> e;
  if (e == 1) {
    for (int i = 0; i < n; i++) {
      cout << "X0[" << i + 1 << "] = ";
      cin >> X0[i];
    }
    cout << "e = ";
    cin >> e;
  } else {
    X0[0] = 0.5, X0[1] = 0.5, X0[2] = 0.5, e = 0.001;
  }
  cout << endl;
  niut(X0, e);
  cout << endl;
  return 0;
}