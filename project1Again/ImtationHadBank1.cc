#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <process.h>
using namespace std;
const string ClientsFileName = "C:/Tutourials/HadhoudAdvices/projects/project!/Bank1.txt";

// Declare Functions
void ShowMainMenue();
void ShowTransActionMenuScreen();

struct sClient
{
  string AccountNumber = "";
  string PINcode = "";
  string Name = "";
  string Phone = "";
  double AccountBalance;
  bool MarkForDelete = false;
};

vector<string> SplitString(string s, string Delim)
{
  vector<string> vWords;
  string word = "";
  short pos = 0;
  while ((pos = s.find(Delim)) != string::npos)
  {
    word = s.substr(0, pos);
    if (word != "")
    {
      vWords.push_back(word);
    }
    s.erase(0, pos + Delim.length());
  }
  if (s != "")
  {
    vWords.push_back(s);
  }
  return vWords;
}

sClient ConvertLineToRecord(string Line, string seperator = "#//#")
{
  sClient Client;
  vector<string> word = SplitString(Line, seperator);
  Client.AccountNumber = word[0];
  Client.PINcode = word[1];
  Client.Name = word[2];
  Client.Phone = word[3];
  Client.AccountBalance = stod(word[4]);
  return Client;
}

string ConvertRecordToLine(sClient Client, string seperator = "#//#")
{
  string line = "";
  line = line + Client.AccountNumber + seperator;
  line = line + Client.PINcode + seperator;
  line = line + Client.Name + seperator;
  line = line + Client.Phone + seperator;
  line = line + to_string(Client.AccountBalance);
  return line;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
  vector<sClient> vClients;
  fstream MyFile;
  MyFile.open(FileName, ios::in);
  if (MyFile.is_open())
  {
    string Line;
    sClient Client;
    while (getline(MyFile, Line))
    {
      Client = ConvertLineToRecord(Line);
      if (Client.AccountNumber == AccountNumber)
      {
        MyFile.close();
        return true;
      }
      vClients.push_back(Client);
    }
    MyFile.close();
  }
  return false;
}

sClient ReadNewClient()
{
  sClient Client;
  cout << "Enter Account number ?";
  getline(cin >> ws, Client.AccountNumber);
  while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    ;
  {
    cout << "\nClient With [" << Client.AccountNumber << "already Exists\nEnter Another Account Number\n";
    getline(cin >> ws, Client.AccountNumber);
  }
  cout << "Enter PinCode?";
  getline(cin, Client.PINcode);
  cout << "Enter Name ?";
  getline(cin, Client.Name);

  cout << "Enter Phone? ";
  getline(cin, Client.Phone);

  cout << "Enter AccountBalance? ";
  cin >> Client.AccountBalance;

  return Client;
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

    while (getline(MyFile, Line))
    {
      Client = ConvertLineToRecord(Line);
      vClients.push_back(Client);
    }
    MyFile.close();
  }
  return vClients;
}

void PrintClientRecordLine(sClient Client)
{
  cout << "| " << setw(15) << left << Client.AccountNumber;
  cout << "| " << setw(10) << left << Client.PINcode;
  cout << "| " << setw(40) << left << Client.Name;
  cout << "| " << setw(12) << left << Client.Phone;
  cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

  cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  cout << "| " << left << setw(15) << "Accout Number";
  cout << "| " << left << setw(10) << "Pin Code";
  cout << "| " << left << setw(40) << "Client Name";
  cout << "| " << left << setw(12) << "Phone";
  cout << "| " << left << setw(12) << "Balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  if (vClients.size() == 0)
    cout << "\t\t\t\tNo Clients Available In the System!";
  else

    for (sClient Client : vClients)
    {

      PrintClientRecordLine(Client);
      cout << endl;
    }

  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
}

void PrintClientCard(sClient Client)
{
  cout << "\nThe following are the client details:\n";
  cout << "-----------------------------------";
  cout << "\nAccout Number: " << Client.AccountNumber;
  cout << "\nPin Code     : " << Client.PINcode;
  cout << "\nName         : " << Client.Name;
  cout << "\nPhone        : " << Client.Phone;
  cout << "\nAccount Balance: " << Client.AccountBalance;
  cout << "\n-----------------------------------\n";
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

sClient ChangeClientRecord(string AccountNumber)
{
  sClient Client;

  Client.AccountNumber = AccountNumber;

  cout << "\n\nEnter PinCode? ";
  getline(cin >> ws, Client.PINcode);

  cout << "Enter Name? ";
  getline(cin, Client.Name);

  cout << "Enter Phone? ";
  getline(cin, Client.Phone);

  cout << "Enter AccountBalance? ";
  cin >> Client.AccountBalance;
  return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

  for (sClient &C : vClients)
  {

    if (C.AccountNumber == AccountNumber)
    {
      C.MarkForDelete = true;
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

      if (C.MarkForDelete == false)
      {
        // we only write records that are not marked for delete.
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

void AddNewClient()
{
  sClient Client;
  Client = ReadNewClient();
  AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
  char AddMore = 'Y';
  do
  {
    // system("cls");
    cout << "Adding New Client:\n\n";

    AddNewClient();
    cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
    cin >> AddMore;

  } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
  sClient Client;
  char Answer = 'n';

  if (FindClientByAccountNumber(AccountNumber, vClients, Client))
  {

    PrintClientCard(Client);

    cout << "\n\nAre you sure you want delete this client? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
      MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
      SaveCleintsDataToFile(ClientsFileName, vClients);

      // Refresh Clients
      vClients = LoadCleintsDataFromFile(ClientsFileName);

      cout << "\n\nClient Deleted Successfully.";
      return true;
    }
  }
  else
  {
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
  }
  return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

  sClient Client;
  char Answer = 'n';

  if (FindClientByAccountNumber(AccountNumber, vClients, Client))
  {

    PrintClientCard(Client);
    cout << "\n\nAre you sure you want update this client? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
      for (sClient &C : vClients)
      {
        if (C.AccountNumber == AccountNumber)
        {
          C = ChangeClientRecord(AccountNumber);
          break;
        }
      }

      SaveCleintsDataToFile(ClientsFileName, vClients);

      cout << "\n\nClient Updated Successfully.";
      return true;
    }
  }
  else
  {
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
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

void ShowDeleteClientScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tDelete Client Screen";
  cout << "\n-----------------------------------\n";

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  string AccountNumber = ReadClientAccountNumber();
  DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tUpdate Client Info Screen";
  cout << "\n-----------------------------------\n";

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  string AccountNumber = ReadClientAccountNumber();
  UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tAdd New Clients Screen";
  cout << "\n-----------------------------------\n";

  AddNewClients();
}

void ShowFindClientScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tFind Client Screen";
  cout << "\n-----------------------------------\n";

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  sClient Client;
  string AccountNumber = ReadClientAccountNumber();
  if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    PrintClientCard(Client);
  else
    cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tProgram Ends :-)";
  cout << "\n-----------------------------------\n";
}

enum enMainMenueOptions
{
  eListClients = 1,
  eAddNewClient = 2,
  eDeleteClient = 3,
  eUpdateClient = 4,
  eFindClient = 5,
  eTransAction = 6,
  eExit = 7
};

void GoBackToMainMenue()
{
  cout << "\n\nPress any key to go back to Main Menue...";
  system("pause>0");
  ShowMainMenue();
}

void GoBackToTransActionMenue()
{
  cout << "\n\nPress any key to go back to TransActions Menue...";
  system("pause>0");
  ShowTransActionMenuScreen();
}

short ReadMainMenueOption()
{
  cout << "Choose what do you want to do? [1 to 7]? ";
  short Choice = 0;
  cin >> Choice;

  return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
  switch (MainMenueOption)
  {
  case enMainMenueOptions::eListClients:
  {
    // system("cls");
    ShowAllClientsScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eAddNewClient:
    // system("cls");
    ShowAddNewClientsScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eDeleteClient:
    // system("cls");
    ShowDeleteClientScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eUpdateClient:
    // system("cls");
    ShowUpdateClientScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eFindClient:
    // system("cls");
    ShowFindClientScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eTransAction:
    // system("cls");
    ShowTransActionMenuScreen();

  case enMainMenueOptions::eExit:
    // system("cls");
    ShowEndScreen();
    break;
  }
}

// Deposit term============
sClient Deposit(sClient &Client, double Added)
{
  Client.AccountBalance += Added;
  return Client;
}

bool DepositScreen()
{
  vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
  string ACcountNumber = ReadClientAccountNumber();
  while (!ClientExistsByAccountNumber(ACcountNumber, ClientsFileName))
  {
    cout << "The Account with ACcount Number [" << ACcountNumber << "] Does not exsit \n";
    ACcountNumber = ReadClientAccountNumber();
  }

  for (sClient &C : vClient)
  {
    if (C.AccountNumber == ACcountNumber)
    {

      PrintClientCard(C);
      double Added;
      cout << "enter the Deposit Amount \n";
      cin >> Added;
      cout << "Are you sure you want Perform this action \n";
      char yes = 'y';
      if (toupper(yes) == toupper('y'))
      {
        Deposit(C, Added);
        cout << "Done successfuly New Balance is " << C.AccountBalance << "\n";
      }
      SaveCleintsDataToFile(ClientsFileName, vClient);

      return true;
    }
  }

  return false;
}

void ShowDepositScreen()
{

  cout << "---------------------------\n";
  cout << "\tDeposit Screen\n";
  cout << "---------------------------\n";
  DepositScreen();
}

// WithDraw term=============
bool WithDraw()
{
  vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
  string ACcountNumber = ReadClientAccountNumber();
  while (!ClientExistsByAccountNumber(ACcountNumber, ClientsFileName))
  {
    cout << "The Account with ACcount Number [" << ACcountNumber << "] Does not exsit \n";
    ACcountNumber = ReadClientAccountNumber();
  }

  for (sClient &C : vClient)
  {
    if (C.AccountNumber == ACcountNumber)
    {

      PrintClientCard(C);
      double Added;
      cout << "enter the WithDraw Amount \n";
      cin >> Added;
      while (Added > C.AccountBalance)
      {
        cout << "you balance isn't enough ,enter the WithDraw Amount \n";
        cin >> Added;
      }
      cout << "Are you sure you want Perform this action \n";
      char yes = 'y';
      if (toupper(yes) == toupper('y'))
      {
        Deposit(C, -1 * Added);
        cout << "Done successfuly New Balance is " << C.AccountBalance << "\n";
      }
      SaveCleintsDataToFile(ClientsFileName, vClient);

      return true;
    }
  }

  return false;
}

void showWithDraw()
{
  cout << "---------------------------\n";
  cout << "\tWithDraw Screen\n";
  cout << "---------------------------\n";
  WithDraw();
}

enum enTransAction
{
  eDeposit = 1,
  eWithdraw = 2,
  eTotalBalance = 3,
  eMainMenue = 4
};

short ReadTransActionMenueOption()
{
  cout << "Choose what do you want to do? [1 to 4]? ";
  short Choice = 0;
  cin >> Choice;

  return Choice;
}

void PrintCLientBalance(sClient Client)
{
  cout << "| " << setw(15) << left << Client.AccountNumber;
  cout << "| " << setw(40) << left << Client.Name;
  cout << "| " << setw(12) << left << Client.AccountBalance;
}

void TotalBalances()
{
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

  cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  cout << "| " << left << setw(15) << "Accout Number";
  cout << "| " << left << setw(40) << "Client Name";
  cout << "| " << left << setw(12) << "Balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  if (vClients.size() == 0)
    cout << "\t\t\t\tNo Clients Available In the System!";
  else

    for (sClient Client : vClients)
    {

      PrintCLientBalance(Client);
      cout << endl;
    }

  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
}

void PerfromTransActionMenue(enTransAction transOption)
{
  switch (transOption)
  {
  case enTransAction::eDeposit:
    ShowDepositScreen();
    break;
  case enTransAction::eWithdraw:
    showWithDraw();
    break;
  case enTransAction::eTotalBalance:
    TotalBalances();
    break;
  case enTransAction::eMainMenue:
    ShowMainMenue();
    break;
  default:
    ShowTransActionMenuScreen();
    break;
  }
}

void ShowTransActionMenuScreen()
{
  cout << "===========================================\n";
  cout << "\t\t TransAction menue Screen\n";
  cout << "===========================================\n";
  cout << "[1]Deposit\n";
  cout << "[2]withdraw\n";
  cout << "[3]Total Balances\n";
  cout << "[4]Main Menue\n";
  cout << "===========================================\n";
  cout << "chose what do want to do \n";
  PerfromTransActionMenue(enTransAction(ReadTransActionMenueOption()));
}

void ShowMainMenue()
{
  // system("cls");
  cout << "===========================================\n";
  cout << "\t\tMain Menue Screen\n";
  cout << "===========================================\n";
  cout << "\t[1] Show Client List.\n";
  cout << "\t[2] Add New Client.\n";
  cout << "\t[3] Delete Client.\n";
  cout << "\t[4] Update Client Info.\n";
  cout << "\t[5] Find Client.\n";
  cout << "\t[6] TransActoins/\n";
  cout << "\t[7] Exit.\n";
  cout << "===========================================\n";
  PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
  ShowMainMenue();

  // system("pause>0");

  return 0;
}
