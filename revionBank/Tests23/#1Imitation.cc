#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const string ClientsFileName = "C:/Tutourials/HadhoudAdvices/projects/revionBank/Bank5.txt";
const string UsersFileName = "C:/Tutourials/HadhoudAdvices/projects/revionBank/Tests23/Users.txt";

void ShowLoginScreen();
void LogOut();
void ShowMangeUsersMenueSreen();
void ShowTransactionsMenue();
void ShowMainMenue();
struct sClient
{
  string AccountNumber;
  string PinCode;
  string Name;
  string Phone;
  double AccountBalance;
  bool MarkForDelete = false;
};

struct stUser
{
  string Name;
  string Password;
  short Permissions = 0;
  bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{

  vector<string> vString;

  short pos = 0;
  string sWord; // define a string variable

  // use find() function to get the position of the delimiters
  while ((pos = S1.find(Delim)) != std::string::npos)
  {
    sWord = S1.substr(0, pos); // store the word
    if (sWord != "")
    {
      vString.push_back(sWord);
    }

    S1.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
  }

  if (S1 != "")
  {
    vString.push_back(S1); // it adds last word of the string.
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

stUser ConvertLinetoUserRecord(string Line, string Seperator = "#//#")
{

  stUser User;
  vector<string> vUserData;

  vUserData = SplitString(Line, Seperator);

  User.Name = vUserData[0];
  User.Password = vUserData[1];
  User.Permissions = stoi(vUserData[2]);

  return User;
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

string ConvertUserRecordToLine(stUser User, string Seperator = "#//#")
{

  string stUserRecord = "";

  stUserRecord += User.Name + Seperator;
  stUserRecord += User.Password + Seperator;
  stUserRecord += to_string(User.Permissions);

  return stUserRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string ClientsFileName)
{

  vector<sClient> vClients;

  fstream MyFile;
  MyFile.open(ClientsFileName, ios::in); // read Mode

  if (MyFile.is_open())
  {

    string Line;
    sClient Client;

    while (getline(MyFile, Line))
    {

      Client = ConvertLinetoRecord(Line);
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

  cout << "Enter Account Number? ";
  // Usage of std::ws will extract all the whiteSpace Character
  getline(cin >> ws, Client.AccountNumber);
  while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
  {
    cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
  }

  cout << "Enter PinCode? ";
  getline(cin, Client.PinCode);

  cout << "Enter Name? ";
  getline(cin, Client.Name);

  cout << "Enter Phone? ";
  getline(cin, Client.Phone);

  cout << "Enter AccountBalance? ";
  cin >> Client.AccountBalance;

  return Client;
}

vector<sClient> LoadCleintsDataFromFile(string ClientsFileName)
{

  vector<sClient> vClients;

  fstream MyFile;
  MyFile.open(ClientsFileName, ios::in); // read Mode

  if (MyFile.is_open())
  {

    string Line;
    sClient Client;

    while (getline(MyFile, Line))
    {

      Client = ConvertLinetoRecord(Line);

      vClients.push_back(Client);
    }

    MyFile.close();
  }

  return vClients;
}

vector<stUser> LoadUsersDataFromFile(string UsersFileName)
{

  vector<stUser> vUsers;

  fstream MyFile;
  MyFile.open(UsersFileName, ios::in); // read Mode

  if (MyFile.is_open())
  {

    string Line;
    stUser User;

    while (getline(MyFile, Line))
    {

      User = ConvertLinetoUserRecord(Line);

      vUsers.push_back(User);
    }

    MyFile.close();
  }

  return vUsers;
}

void PrintClientRecordLine(sClient Client)
{

  cout << "| " << setw(15) << left << Client.AccountNumber;
  cout << "| " << setw(10) << left << Client.PinCode;
  cout << "| " << setw(40) << left << Client.Name;
  cout << "| " << setw(12) << left << Client.Phone;
  cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientRecordBalanceLine(sClient Client)
{

  cout << "| " << setw(15) << left << Client.AccountNumber;
  cout << "| " << setw(40) << left << Client.Name;
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

void ShowTotalBalances()
{

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

  cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  cout << "| " << left << setw(15) << "Accout Number";
  cout << "| " << left << setw(40) << "Client Name";
  cout << "| " << left << setw(12) << "Balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  double TotalBalances = 0;

  if (vClients.size() == 0)
    cout << "\t\t\t\tNo Clients Available In the System!";
  else

    for (sClient Client : vClients)
    {

      PrintClientRecordBalanceLine(Client);
      TotalBalances += Client.AccountBalance;

      cout << endl;
    }

  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
  cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}

void PrintClientCard(sClient Client)
{
  cout << "\nThe following are the client details:\n";
  cout << "-----------------------------------";
  cout << "\nAccout Number: " << Client.AccountNumber;
  cout << "\nPin Code     : " << Client.PinCode;
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
  getline(cin >> ws, Client.PinCode);

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
  AddDataLineToFile(UsersFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
  char AddMore = 'Y';
  do
  {
    // std::cout << "\033[2J\033[H";
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
    return false;
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
    return false;
  }
  return false;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{

  char Answer = 'n';

  cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {

    for (sClient &C : vClients)
    {
      if (C.AccountNumber == AccountNumber)
      {
        C.AccountBalance += Amount;
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

void ShowDepositScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tDeposit Screen";
  cout << "\n-----------------------------------\n";

  sClient Client;

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  string AccountNumber = ReadClientAccountNumber();

  while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
  {
    cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
    AccountNumber = ReadClientAccountNumber();
  }

  PrintClientCard(Client);

  double Amount = 0;
  cout << "\nPlease enter deposit amount? ";
  cin >> Amount;

  DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tWithdraw Screen";
  cout << "\n-----------------------------------\n";

  sClient Client;

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  string AccountNumber = ReadClientAccountNumber();

  while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
  {
    cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
    AccountNumber = ReadClientAccountNumber();
  }

  PrintClientCard(Client);

  double Amount = 0;
  cout << "\nPlease enter withdraw amount? ";
  cin >> Amount;

  // Validate that the amount does not exceeds the balance
  while (Amount > Client.AccountBalance)
  {
    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
    cout << "Please enter another amount? ";
    cin >> Amount;
  }

  DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{

  ShowTotalBalances();
}

enum enUserMenueOptions
{
  ListUsers = 1,
  AddUser = 2,
  DelUser = 3,
  UpdateUser = 4,
  FindUser = 5,
  MainMenue = 6
};

enum enTransactionsMenueOptions
{
  eDeposit = 1,
  eWithdraw = 2,
  eShowTotalBalance = 3,
  eShowMainMenue = 4
};

enum enMainMenueOptions
{
  eListClients = 1,
  eAddNewClient = 2,
  eDeleteClient = 3,
  eUpdateClient = 4,
  eFindClient = 5,
  eShowTransactionsMenue = 6,
  mangeUser = 7,
  eLogOut = 8
};

void GoBackToMainMenue()
{
  cout << "\n\n Press any Key to go back to Main Menue...";
  string anyKey;
  cin >> anyKey;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
  cout << "\n\nPress any key to go back to Transactions Menue...";
  string anyKey;
  cin >> anyKey;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
{
  cout << "Choose what do you want to do? [1 to 4]? ";
  short Choice = 0;
  cin >> Choice;

  return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
  switch (TransactionMenueOption)
  {
  case enTransactionsMenueOptions::eDeposit:
  {
    std::cout << "\033[2J\033[H";
    ShowDepositScreen();
    GoBackToTransactionsMenue();
    break;
  }

  case enTransactionsMenueOptions::eWithdraw:
  {
    std::cout << "\033[2J\033[H";
    ShowWithDrawScreen();
    GoBackToTransactionsMenue();
    break;
  }

  case enTransactionsMenueOptions::eShowTotalBalance:
  {
    std::cout << "\033[2J\033[H";
    ShowTotalBalancesScreen();
    GoBackToTransactionsMenue();
    break;
  }

  case enTransactionsMenueOptions::eShowMainMenue:
  {

    ShowMainMenue();
  }
  }
}

void ShowTransactionsMenue()
{
  std::cout << "\033[2J\033[H";
  cout << "===========================================\n";
  cout << "\t\tTransactions Menue Screen\n";
  cout << "===========================================\n";
  cout << "\t[1] Deposit.\n";
  cout << "\t[2] Withdraw.\n";
  cout << "\t[3] Total Balances.\n";
  cout << "\t[4] Main Menue.\n";
  cout << "===========================================\n";
  PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
  cout << "Choose what do you want to do? [1 to 8]? ";
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
    std::cout << "\033[2J\033[H";
    ShowAllClientsScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eAddNewClient:
    std::cout << "\033[2J\033[H";
    ShowAddNewClientsScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eDeleteClient:
    std::cout << "\033[2J\033[H";
    ShowDeleteClientScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eUpdateClient:
    std::cout << "\033[2J\033[H";
    ShowUpdateClientScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eFindClient:
    std::cout << "\033[2J\033[H";
    ShowFindClientScreen();
    GoBackToMainMenue();
    break;

  case enMainMenueOptions::eShowTransactionsMenue:
    std::cout << "\033[2J\033[H";
    ShowTransactionsMenue();
    break;
  case enMainMenueOptions::mangeUser:
    std::cout << "\033[2J\033[H";
    ShowMangeUsersMenueSreen();
    break;
  case enMainMenueOptions::eLogOut:
    std::cout << "\033[2J\033[H";
    LogOut();
    break;
  }
}

void ShowMainMenue()
{
  std::cout << "\033[2J\033[H";
  cout << "===========================================\n";
  cout << "\t\tMain Menue Screen\n";
  cout << "===========================================\n";
  cout << "\t[1] Show Client List.\n";
  cout << "\t[2] Add New Client.\n";
  cout << "\t[3] Delete Client.\n";
  cout << "\t[4] Update Client Info.\n";
  cout << "\t[5] Find Client.\n";
  cout << "\t[6] Transactions.\n";
  cout << "\t[7] Manage Users.\n";
  cout << "\t[8] Logout.\n";
  cout << "===========================================\n";
  PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

// User Feature ===================================//////===========================

bool UserExistsByUserName(string UserName, string UsersFileName)
{

  vector<stUser> vUsers;

  fstream MyFile;
  MyFile.open(UsersFileName, ios::in); // read Mode

  if (MyFile.is_open())
  {

    string Line;
    stUser User;

    while (getline(MyFile, Line))
    {

      User = ConvertLinetoUserRecord(Line);
      if (User.Name == UserName)
      {
        MyFile.close();
        return true;
      }
    }

    MyFile.close();
  }
  return false;
}

stUser ReadNewUser()
{
  stUser User;

  cout << "Enter User Name? ";
  // Usage of std::ws will extract all the whiteSpace Character
  getline(cin >> ws, User.Name);
  while (UserExistsByUserName(User.Name, UsersFileName))
  {
    cout << "\nClient with [" << User.Name << "] already exists, Enter another Account Number? ";
    getline(cin >> ws, User.Password);
  }

  cout << "Enter PassWord? ";
  getline(cin, User.Password);

  cout << "Enter PerMissions? ";
  // getline(cin, );

  return User;
}

short ReadMangeUsersOptions()
{
  cout << "Choose what do you want to do? [1 to 7]? ";
  short Choice = 0;
  cin >> Choice;

  return Choice;
}

void GoBackToManageUserMenue()
{
  cout << "\n\nPress any key to go back to Manage User Menue...";
  string anyKey;
  cin >> anyKey;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  ShowMangeUsersMenueSreen();
}

void PrintUserRecord(stUser Users)
{

  cout << "| " << setw(15) << left << Users.Name;
  cout << "| " << setw(40) << left << Users.Password;
  cout << "| " << setw(12) << left << Users.Permissions;
}

void AddNewUser()
{
  stUser User;
  User = ReadNewUser();
  AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers()
{
  char AddMore = 'Y';
  do
  {
    // std::cout << "\033[2J\033[H";
    cout << "Adding New User:\n\n";

    AddNewUser();
    cout << "\nUser Added Successfully, do you want to add more clients? Y/N? ";

    cin >> AddMore;

  } while (toupper(AddMore) == 'Y');
}

void ShowAddNewUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tAdd New Users Screen";
  cout << "\n-----------------------------------\n";
  AddNewUsers();
}

string ReadUserName()
{
  string UserName = "";

  cout << "\nPlease enter UserName? ";
  cin >> UserName;
  return UserName;
}

void PrintUSerCard(stUser User)
{
  cout << "\nThe following are the User details:\n";
  cout << "-----------------------------------";
  cout << "\nUser Name        : " << User.Name;
  cout << "\nUser Password    : " << User.Password;
  cout << "\nUser Permissions : " << User.Permissions;
  cout << "\n-----------------------------------\n";
}

bool FindUserByUserName(string UserName, vector<stUser> vUsers, stUser &User)
{

  for (stUser U : vUsers)
  {

    if (U.Name == UserName)
    {
      User = U;
      return true;
    }
  }
  return false;
}

bool MarkUserForDeleteByuserName(string UserName, vector<stUser> &vUsers)
{

  for (stUser &U : vUsers)
  {

    if (U.Name == UserName)
    {
      U.MarkForDelete = true;
      return true;
    }
  }

  return false;
}

vector<stUser> SaveUsersDataToFile(string UsersFileName, vector<stUser> vUsers)
{

  fstream MyFile;
  MyFile.open(UsersFileName, ios::out); // overwrite

  string DataLine;

  if (MyFile.is_open())
  {

    for (stUser U : vUsers)
    {

      if (U.MarkForDelete == false)
      {
        // we only write records that are not marked for delete.
        DataLine = ConvertUserRecordToLine(U);
        MyFile << DataLine << endl;
      }
    }

    MyFile.close();
  }

  return vUsers;
}

bool DeleteUserByUserName(string UserName, vector<stUser> vUsers)
{

  stUser User;
  char Answer = 'n';

  if (FindUserByUserName(UserName, vUsers, User))
  {

    PrintUSerCard(User);

    cout << "\n\nAre you sure you want delete this User ? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
      MarkUserForDeleteByuserName(UserName, vUsers);
      SaveUsersDataToFile(UsersFileName, vUsers);

      // Refresh Users
      vUsers = LoadUsersDataFromFile(ClientsFileName);

      cout << "\n\nClient Deleted Successfully.";
      return true;
    }
  }
  else
  {
    cout << "\nUser with Account Number (" << UserName << ") is Not Found!";
    return false;
  }
  return false;
}

void ShowDeleteUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tDelete User Screen";
  cout << "\n-----------------------------------\n";

  vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);
  string UserName = ReadUserName();
  DeleteUserByUserName(UserName, vUser);
}

stUser ChangeUserRecord(string UserName)
{
  stUser User;

  User.Name = UserName;
  cout << "\n\nEnter PassWord  ";
  getline(cin >> ws, User.Password);

  cout << "Enter Permissions :  ";
  // cin>> User.Permissions;

  return User;
}

bool UpdateUserByUserName(string UserName, vector<stUser> &vUsers)
{

  stUser User;
  char Answer = 'n';

  if (FindUserByUserName(UserName, vUsers, User))
  {

    PrintUSerCard(User);
    cout << "\n\nAre you sure you want update this User? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

      for (stUser U : vUsers)
      {
        if (U.Name == UserName)
        {
          U = ChangeUserRecord(UserName);
          break;
        }
      }

      SaveUsersDataToFile(UsersFileName, vUsers);
      cout << "\n\nUser Updated Successfully.";
      return true;
    }
  }
  else
  {
    cout << "\nUser with User Name (" << UserName << ") is Not Found!";
    return false;
  }
  return false;
}

void ShowUpdateUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tUpdate User Info Screen";
  cout << "\n-----------------------------------\n";

  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
  string UserName = ReadUserName();
  UpdateUserByUserName(UserName, vUsers);
}

void ShowFindUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tFind User Screen";
  cout << "\n-----------------------------------\n";

  vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);
  string UserName = ReadUserName();
  stUser User;

  if (FindUserByUserName(UserName, vUser, User))
    PrintUSerCard(User);
  else
    cout << "\nUser with User Name [" << UserName << "] is not found!";
}

void ShowUsersList()
{

  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

  cout << "\n\t\t\t\t\tBalances List (" << vUsers.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  cout << "| " << left << setw(15) << "User Name";
  cout << "| " << left << setw(40) << "User Password";
  cout << "| " << left << setw(12) << "Permissions";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  if (vUsers.size() == 0)
  {
    cout << "\t\t\t\tNo Users Available In the System!";
  }
  else
  {
    for (stUser User : vUsers)
    {
      PrintUserRecord(User);
      cout << endl;
    }
  }
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
}

void PerformManageUserMenue(enUserMenueOptions UserMainMenue)
{
  switch (UserMainMenue)
  {
  case enUserMenueOptions::ListUsers:
    cout << "\033[2J\033[H";
    ShowUsersList();
    GoBackToManageUserMenue();

    break;
  case enUserMenueOptions::AddUser:
    cout << "\033[2J\033[H";
    ShowAddNewUserScreen();
    GoBackToManageUserMenue();
    break;
  case enUserMenueOptions::DelUser:
    cout << "\033[2J\033[H";
    ShowDeleteUserScreen();
    GoBackToManageUserMenue();
    break;
  case enUserMenueOptions::UpdateUser:
    cout << "\033[2J\033[H";
    ShowUpdateUserScreen();
    GoBackToManageUserMenue();
    break;
  case enUserMenueOptions::FindUser:
    cout << "\033[2J\033[H";
    ShowFindUserScreen();
    GoBackToManageUserMenue();
    break;

  case enUserMenueOptions::MainMenue:
    ShowMainMenue();

  default:
    break;
  }
}

void ShowMangeUsersMenueSreen()
{
  cout << "\033[2J\033[H";
  cout << "===========================================\n";
  cout << "\t\tManage Users Menue Screen\n";
  cout << "===========================================\n";
  cout << "\t[1] List Users.\n";
  cout << "\t[2] Add New User.\n";
  cout << "\t[3] Delete User.\n";
  cout << "\t[4] Update User Info.\n";
  cout << "\t[5] Find User.\n";
  cout << "\t[6] Main Menue.\n";
  cout << "===========================================\n";
  PerformManageUserMenue(enUserMenueOptions(ReadMangeUsersOptions()));
}

stUser ReadUserToLog()
{
  stUser User;
  cout << "Enter the User Name \n";
  getline(cin >> ws, User.Name);
  cout << "Enter the Password \n";
  getline(cin >> ws, User.Password);
  return User;
}

bool CheckUserPassword(stUser User, vector<stUser> vUsers)
{
  for (stUser U : vUsers)
  {
    if (U.Password == User.Password)
    {
      return true;
    }
  }
  return false;
}

void LogOperat()
{
  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
  stUser User = ReadUserToLog();

  if (UserExistsByUserName(User.Name, UsersFileName))
  {
    if (CheckUserPassword(User, vUsers))
    {
      ShowMainMenue();
    }
    else
    {

      cout << "The password is not Correct \n";
    }
  }
  else
  {
    cout << "the User doesn't Exsit ";
  }
}

void ShowLoginScreen()
{
  std::cout << "\033[2J\033[H";
  cout << "\n-----------------------------------\n";
  cout << "\tLogin Screen";
  cout << "\n-----------------------------------\n";
  char Yes = 'y';
  while (toupper(Yes) == toupper('y'))
  {
    LogOperat();
    cout << "Do You want To Log Agin ?Y/n  \n";
    cin >> Yes;
  }
}

void LogOut()
{
  ShowLoginScreen();
}

// bool AccsessUsers(enMainMenueOptions MainChoose)
// {
// }

int main()
{
  ShowLoginScreen();
  system("pause>0");
  return 0;

  return 0;
}