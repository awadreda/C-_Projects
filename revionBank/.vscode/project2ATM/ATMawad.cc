#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;
const string ClientsFileName = "C:/Tutourials/HadhoudAdvices/projects/revionBank/Bank5.txt"; // File name for storing client information
void Login();
void ShowATMMainMenue();
enum enClientsATMMenueOptions
{
  eQuickWithdraw = 1,
  eWithdraw = 2,
  eDeposit = 3,
  eChecklBalance = 4,
  eLogOut = 5
};

enum enQuickWithDraw
{
  eTwinty = 1,
  efifty = 2,
  eOneHunderd = 3,
  eTwoHunderd = 4,

  eOneHunderd4 = 5,

  eOneHunderd6 = 6,
  eOneHunderd8 = 7,
  eOneHunderd10 = 8,
  eeExit = 9

};

struct sClient
{
  string AccountNumber;
  string PinCode;
  string Name;
  string Phone;
  double AccountBalance;
  bool MarkForDelete = false;
};
sClient Client;

vector<string> SplitString(string S1, string Delim)
{
  vector<string> vString;
  short pos = 0;
  string sWord;

  // Use find() function to get the position of the delimiters
  while ((pos = S1.find(Delim)) != std::string::npos)
  {
    sWord = S1.substr(0, pos);

    // Store the word if it is not empty
    if (sWord != "")
    {
      vString.push_back(sWord);
    }

    // Erase until the position and move to the next word
    S1.erase(0, pos + Delim.length());
  }

  // Add the last word of the string
  if (S1 != "")
  {
    vString.push_back(S1);
  }

  return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
  sClient Client;
  vector<string> vClientData;
  vClientData = SplitString(Line, Seperator);
  Client.AccountNumber = vClientData[0];
  Client.PinCode = vClientData[1];
  Client.Name = vClientData[2];
  Client.Phone = vClientData[3];
  Client.AccountBalance = stod(vClientData[4]); // cast string to double
  return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
  string stClientRecord = "";
  stClientRecord += Client.AccountNumber + Seperator;
  stClientRecord += Client.PinCode + Seperator;
  stClientRecord += Client.Name + Seperator;
  stClientRecord += Client.Phone + Seperator;
  stClientRecord += to_string(Client.AccountBalance);
  return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
  vector<sClient> vClients;
  fstream MyFile;
  MyFile.open(FileName, ios::in); // read Mode

  if (MyFile.is_open())
  {
    string Line;
    sClient Client;

    // Read each line in the file
    while (getline(MyFile, Line))
    {
      Client = ConvertLinetoRecord(Line);

      // Check if the account number matches
      if (Client.AccountNumber == AccountNumber)
      {
        MyFile.close();
        return true;
      }

      // Add the client to the vector
      vClients.push_back(Client);
    }

    MyFile.close();
  }

  return false;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
  vector<sClient> vClients;
  fstream MyFile;
  MyFile.open(FileName, ios::in); // read Mode

  if (MyFile.is_open())
  {
    string Line;
    sClient Client;

    // Read each line in the file and convert to client record
    while (getline(MyFile, Line))
    {
      Client = ConvertLinetoRecord(Line);
      vClients.push_back(Client);
    }

    MyFile.close();
  }

  return vClients;
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{
  for (sClient C : vClients)
  {
    if (C.AccountNumber == AccountNumber)
    {
      Client = C;
      return true;
    }
  }
  return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
  fstream MyFile;
  MyFile.open(FileName, ios::out); // overwrite
  string DataLine;

  if (MyFile.is_open())
  {
    for (sClient C : vClients)
    {
      if (!C.MarkForDelete)
      {
        // Write records that are not marked for delete
        DataLine = ConvertRecordToLine(C);
        MyFile << DataLine << endl;
      }
    }

    MyFile.close();
  }

  return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
  fstream MyFile;
  MyFile.open(FileName, ios::out | ios::app);

  if (MyFile.is_open())
  {
    MyFile << stDataLine << endl;
    MyFile.close();
  }
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{
  char Answer = 'n';
  cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
  cin >> Answer;

  if (Answer == 'y' || Answer == 'Y')
  {
    for (sClient &C : vClients)
    {
      if (C.AccountNumber == AccountNumber)
      {
        C.AccountBalance += Amount;
        Client = C;
        SaveCleintsDataToFile(ClientsFileName, vClients);
        cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
        return true;
      }
    }
    return false;
  }
  return false;
}

string ReadClientAccountNumber()
{
  string AccountNumber = "";
  cout << "\nPlease enter AccountNumber? ";
  cin >> AccountNumber;
  return AccountNumber;
}

void ShowDepositScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tDeposit Screen";
  cout << "\n-----------------------------------\n";
  // sClient Client;
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  // string AccountNumber = ReadClientAccountNumber();

  while (!FindClientByAccountNumber(Client.AccountNumber, vClients, Client))
  {
    cout << "\nClient with [" << Client.AccountNumber << "] does not exist.\n";
    Client.AccountNumber = ReadClientAccountNumber();
  }
  // PrintClientCard(Client);
  double Amount = 0;
  cout << "\nPlease enter deposit amount? ";
  cin >> Amount;
  DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tWithdraw Screen";
  cout << "\n-----------------------------------\n";

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  // string AccountNumber = ReadClientAccountNumber();

  while (!FindClientByAccountNumber(Client.AccountNumber, vClients, Client))
  {
    cout << "\nClient with [" << Client.AccountNumber << "] does not exist.\n";
    Client.AccountNumber = ReadClientAccountNumber();
  }

  // PrintClientCard(Client);
  int Amount = 0;

  cout << "\nPlease enter withdraw amount? ";
  cin >> Amount;

  while (Amount % 5 != 0)
  {
    cout << "\nAmount  YOu want Unvalible please enter a %5" << endl;
    cout << "Please enter another amount? ";
    cin >> Amount;
  }

  // Validate that the amount does not exceed the balance
  while (Amount > Client.AccountBalance)
  {
    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
    cout << "Please enter another amount? ";
    cin >> Amount;
  }

  DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount * -1, vClients);
}
void WithDraw(string AccountNumber, double Amount, vector<sClient> vClients)
{
  // Validate that the amount does not exceed the balance
  while (Amount > Client.AccountBalance)
  {
    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
    cout << "Please enter another amount? ";
    cin >> Amount;
  }

  DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void GoBackToATM_MainMenue()
{
  cout << "\n\nPress any key to go back to Main Menu...";
  string input;
  cin >> input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  ShowATMMainMenue();
}

short ReadOption()
{
  cout << "Choose what do you want to do? [1 to 9]? ";
  short Choice = 0;
  cin >> Choice;
  return Choice;
}
void PerfromQuickDraw(enQuickWithDraw Amount)
{
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  switch (Amount)
  {
  case enQuickWithDraw::eTwinty:
  {
    WithDraw(Client.AccountNumber, 20, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::efifty:
  {
    WithDraw(Client.AccountNumber, 50, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eOneHunderd:
  {
    WithDraw(Client.AccountNumber, 100, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eTwoHunderd:
  {
    WithDraw(Client.AccountNumber, 200, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eOneHunderd4:
  {
    WithDraw(Client.AccountNumber, 400, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eOneHunderd6:
  {
    WithDraw(Client.AccountNumber, 600, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eOneHunderd8:
  {
    WithDraw(Client.AccountNumber, 800, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eOneHunderd10:
  {
    WithDraw(Client.AccountNumber, 1000, vClients);
    //   GoBackToATM_MainMenue();
    break;
  }
  case enQuickWithDraw::eeExit:
  {
    // WithDraw(Client.AccountNumber, 1000, vClients);
    GoBackToATM_MainMenue();
    break;
  }

  default:
    break;
  }
}

void ShowQuickDrawScreen()
{
  cout << "\033[2J\033[H";
  cout << "\n=========================================\n";
  cout << "\tQuick Withdraw ";
  cout << "\n=========================================\n";

  cout << "\t[1] 20" << setw(5) << "\t\t[2]50" << endl;
  cout << "\t[3] 100" << setw(5) << "\t\t[4]200" << endl;
  cout << "\t[5] 400" << setw(5) << "\t\t[6]600" << endl;
  cout << "\t[7] 800" << setw(5) << "\t\t[8]1000" << endl;
  cout << "\t[9] Exit " << endl;
  cout << "\n=========================================\n";
  cout << "Your Balance is :" << Client.AccountBalance << "\n";
  PerfromQuickDraw((enQuickWithDraw)ReadOption());
  // cout<< "Your Balance is :" << Client.AccountBalance << "\n";
}

void ShowCheckBalance()
{
  cout << "\033[2J\033[H";
  cout << "\n=========================================\n";
  cout << "\tYour Balance  ";
  cout << "\n=========================================\n";
  cout << "\n\n\t======   Your Balance is :" << Client.AccountBalance << "   ======\n";
}

void PerfromATMMenueOption(enClientsATMMenueOptions Option)
{
  switch (Option)
  {
  case enClientsATMMenueOptions::eDeposit:
  {
    cout << "\033[2J\033[H";
    ShowDepositScreen();
    GoBackToATM_MainMenue();
    break;
  }
  case enClientsATMMenueOptions::eWithdraw:
  {
    cout << "\033[2J\033[H";
    ShowWithDrawScreen();
    GoBackToATM_MainMenue();
    break;
  }
  case enClientsATMMenueOptions::eQuickWithdraw:
  {
    cout << "\033[2J\033[H";
    ShowQuickDrawScreen();
    GoBackToATM_MainMenue();
    break;
  }
  case enClientsATMMenueOptions::eChecklBalance:
  {
    cout << "\033[2J\033[H";
    ShowCheckBalance();
    GoBackToATM_MainMenue();
    break;
  }
  case enClientsATMMenueOptions::eLogOut:
  {
    Login();
  }
  }
}

void ShowATMMainMenue()
{
  cout << "\033[2J\033[H";
  cout << "===========================================\n";
  cout << "\t\tATM Main Menu Screen\n";
  cout << "===========================================\n";

  cout << "\t[1] Quick Withdraw.\n";
  cout << "\t[2] Normal Withdraw.\n";
  cout << "\t[3] Deposit.\n";
  cout << "\t[4] Check Balance.\n";
  cout << "\t[5] LogOut.\n";
  cout << "===========================================\n";

  PerfromATMMenueOption((enClientsATMMenueOptions)ReadOption());
}

bool FindClientByAccountNubmerAndPInCode(string AccountNumber, string PinCode, sClient &Client)
{
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

  for (sClient C : vClients)
  {
    if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
    {
      Client = C;
      return true;
    }
  }
  return false;
}

bool LoadClient(string AccountNumber, string PinCode)
{
  if (FindClientByAccountNubmerAndPInCode(AccountNumber, PinCode, Client))
    return true;
  else
    return false;
}

void Login()
{
  bool LoginFaild = false;
  string AccountNumber, Password;

  do
  {
    cout << "\033[2J\033[H";
    cout << "\n---------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n---------------------------------\n";

    if (LoginFaild)
    {
      cout << "Invalid AccountNumber/Password!\n";
    }

    cout << "Enter AccountNumber? ";
    cin >> AccountNumber;
    cout << "Enter Password? ";
    cin >> Password;

    LoginFaild = !LoadClient(AccountNumber, Password);

  } while (LoginFaild);

  ShowATMMainMenue();
}

// Main function
int main()
{
  // Login();
  Login();
  string input;
  cin >> input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return 0;
}
