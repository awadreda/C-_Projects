#include <iostream>
using namespace std;

int main()
{
  short b = 1;
  short x = 2;
  short Y = 4;
  short z = 8;
  short A = 16;

  cout << (A + b + x + z & z) << "\n";
  return 0;
}