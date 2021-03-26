#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int n = 0;
double e;

double sec_opred(double* a)
{
  return a[0] * a[3] - a[1] * a[2];
}
double third_opred(double* a)
{
  return a[0] * b[4] * c[8] + a[3] * b[1] * c[5] + a[0] * b[7] * c[0] - a[0] * b[4] * c[0] - a[0] * b[1] * c[0] - a[0] * b[7] * c[0];
}

double fun(int i, double x)
{
  switch(i) {
    case(1):
      return x*x + x*x + x*x;
      break;
    case(2):
      return 2*x*x + x*x - 4*x;
      break;
    case(3):
      return 3*x*x - 4*x + x*x;
      break;
    case(4):
      return 2*x - 2*x + 2*x;
      break;
    case(5):
      return 4*x - 2*x - 4;
      break;
    default:
      return 6*x - 4 + 2*x;
      break;
  } 
}

void niut(double* X0)
{
  double present[n];
  double past[n];
  for (int i = 0; i < n; i++) 
    present[i] = X0[i];
}
int main()
{
    double begin, end;
    std::cout << "Do you wanna fill your matrix by yourself:" << std::endl;
    std::cout << "1) Yes" << std::endl;
    std::cout << "2) Use template" << std::endl;
    std::cin >> e;
    if (e == 1) {
      cout << "n = ";
      cin >> n;
      for (int i = 0; i < n; i++) {
        cout << "X0[" << i + 1 << "] = ;
        cin >> X0[i];
      }
      cout << "e = ";
      cin >> e;
    } else {
      n = 
      X0[0] = 0.5, X0[1] = 0.5, X0[2] = 0.5, e = 0.001;
    }
    cout << endl;
    // niut(begin, end, e);
    cout << endl;
    return 0;
}