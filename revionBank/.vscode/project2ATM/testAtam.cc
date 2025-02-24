#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void ShowQuickDrawScreen()
{

  cout << "\n=========================================\n";
  cout << "\tQuick Withdraw ";
  cout << "\n=========================================\n";

  cout << "\t[1] 20" << setw(5) << "\t\t[2]50" << endl;
  cout << "\t[3] 100" << setw(5) << "\t\t[4]200" << endl;
  cout << "\t[5] 400" << setw(5) << "\t\t[6]600" << endl;
  cout << "\t[7] 800" << setw(5) << "\t\t[8]1000" << endl;
  cout << "\t[9] Exit " << endl;
  cout << "\n=========================================\n";
  // cout << "Your Balance is :" << Clinet.AccountBalance << "\n";
}

int main()
{
  ShowQuickDrawScreen();

  return 0;
}