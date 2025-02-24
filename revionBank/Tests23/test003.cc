#include <iostream>
using namespace std;

enum enMainMenueOptions
{
  eListClients = 1,
  eAddNewClient = 2,
  eDeleteClient = 3,
  eUpdateClient = 4,
  eFindClient = 5,
  eShowTransactionsMenue = 6,
  mangeUser = 7,
  eExit = 8
};

short ReadMainMenueOption()
{
  cout << "Choose what do you want to do? [1 to 8]? ";
  short Choice = 0;
  cin >> Choice;

  return Choice;
}

int main()
{
  enMainMenueOptions Choose = (enMainMenueOptions)ReadMainMenueOption();

  // cout << (((((((1 & 2) & 3) & 4) & 5) & 6) & 7) & 8) << "\n";
  if (Choose ==  enMainMenueOptions::eListClients | enMainMenueOptions::eShowTransactionsMenue | enMainMenueOptions::eShowTransactionsMenue | enMainMenueOptions::eUpdateClient | enMainMenueOptions::mangeUser)
    cout << "working ";
  else
    cout << "notWorking ";
  return 0;
}