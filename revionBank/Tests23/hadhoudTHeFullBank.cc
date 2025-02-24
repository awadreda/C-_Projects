#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// User structure to store user information
struct stUser
{
  string UserName;
  string Password;
  int Permissions;
  bool MarkForDelete = false;
};

// Enumeration for various options in the Transactions Menu
enum enTransactionsMenueOptions
{
  eDeposit = 1,
  eWithdraw = 2,
  eShowTotalBalance = 3,
  eShowMainMenue = 4
};

// Enumeration for various options in the Manage Users Menu
enum enManageUsersMenueOptions
{
  eListUsers = 1,
  eAddNewUser = 2,
  eDeleteUser = 3,
  eUpdateUser = 4,
  eFindUser = 5,
  eMainMenue = 6
};

// Enumeration for various options in the Main Menu
enum enMainMenueOptions
{
  eListClients = 1,
  eAddNewClient = 2,
  eDeleteClient = 3,
  eUpdateClient = 4,
  eFindClient = 5,
  eShowTransactionsMenue = 6,
  eManageUsers = 7,
  eExit = 8
};

// Enumeration for various permissions in the Main Menu
enum enMainMenuePermissions
{
  eAll = -1,
  pListClients = 1,
  pAddNewClient = 2,
  pDeleteClient = 4,
  pUpdateClients = 8,
  pFindClient = 16,
  pTranactions = 32,
  pManageUsers = 64
};

const string ClientsFileName = "Clients.txt"; // File name for storing client information
const string UsersFileName = "Users.txt";     // File name for storing user information

stUser CurrentUser; // Variable to store the current user information

// Function declarations
void ShowMainMenue();
void ShowTransactionsMenue();
void ShowManageUsersMenue();
bool CheckAccessPermission(enMainMenuePermissions Permission);
void Login();

// Client structure to store client information
struct sClient
{
  string AccountNumber;
  string PinCode;
  string Name;
  string Phone;
  double AccountBalance;
  bool MarkForDelete = false;
};

// Function to split a string based on a delimiter
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

// Function to convert a line of user data to a user record
stUser ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{
  stUser User;
  vector<string> vUserData;
  vUserData = SplitString(Line, Seperator);
  User.UserName = vUserData[0];
  User.Password = vUserData[1];
  User.Permissions = stoi(vUserData[2]);
  return User;
}

// Function to convert a line of client data to a client record
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

// Function to convert a line of user data to a user record (variant 2)
stUser ConvertUserLinetoRecord2(string Line, string Seperator = "#//#")
{
  stUser User;
  vector<string> vUserData;
  vUserData = SplitString(Line, Seperator);
  User.UserName = vUserData[0];
  User.Password = vUserData[1];
  User.Permissions = stoi(vUserData[2]);
  return User;
}

// Function to convert a client record to a string line
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

// Function to convert a user record to a string line
string ConvertUserRecordToLine(stUser User, string Seperator = "#//#")
{
  string stClientRecord = "";
  stClientRecord += User.UserName + Seperator;
  stClientRecord += User.Password + Seperator;
  stClientRecord += to_string(User.Permissions);
  return stClientRecord;
}

// Function to check if a client exists based on account number
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

// Function to check if a user exists based on username
bool UserExistsByUsername(string Username, string FileName)
{
  fstream MyFile;
  MyFile.open(FileName, ios::in); // read Mode

  if (MyFile.is_open())
  {
    string Line;
    stUser User;

    // Read each line in the file
    while (getline(MyFile, Line))
    {
      User = ConvertUserLinetoRecord(Line);

      // Check if the username matches
      if (User.UserName == Username)
      {
        MyFile.close();
        return true;
      }
    }

    MyFile.close();
  }

  return false;
}

// ... (Continue the rest of the code)

// Function to read details for a new client
sClient ReadNewClient()
{
  sClient Client;

  // Prompt for and read account number
  cout << "Enter Account Number? ";
  getline(cin >> ws, Client.AccountNumber);

  // Check if the account number already exists
  while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
  {
    cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
  }

  // Prompt for and read PinCode, Name, Phone, and AccountBalance
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

// Function to read permissions to set for a new user
int ReadPermissionsToSet()
{
  int Permissions = 0;
  char Answer = 'n';

  cout << "\nDo you want to give full access? y/n? ";
  cin >> Answer;

  if (Answer == 'y' || Answer == 'Y')
  {
    return -1;
  }

  cout << "\nDo you want to give access to:\n";

  cout << "\nShow Client List? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pListClients;
  }

  cout << "\nAdd New Client? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pAddNewClient;
  }

  cout << "\nDelete Client? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pDeleteClient;
  }

  cout << "\nUpdate Client? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pUpdateClients;
  }

  cout << "\nFind Client? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pFindClient;
  }

  cout << "\nTransactions? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pTranactions;
  }

  cout << "\nManage Users? y/n? ";
  cin >> Answer;
  if (Answer == 'y' || Answer == 'Y')
  {
    Permissions += enMainMenuePermissions::pManageUsers;
  }

  return Permissions;
}

// Function to read details for a new user
stUser ReadNewUser()
{
  stUser User;

  // Prompt for and read username
  cout << "Enter Username? ";
  getline(cin >> ws, User.UserName);

  // Check if the username already exists
  while (UserExistsByUsername(User.UserName, UsersFileName))
  {
    cout << "\nUser with [" << User.UserName << "] already exists, Enter another Username? ";
    getline(cin >> ws, User.UserName);
  }

  // Prompt for and read password
  cout << "Enter Password? ";
  getline(cin, User.Password);

  // Set user permissions
  User.Permissions = ReadPermissionsToSet();

  return User;
}

// Function to load user data from file into a vector
vector<stUser> LoadUsersDataFromFile(string FileName)
{
  vector<stUser> vUsers;
  fstream MyFile;
  MyFile.open(FileName, ios::in); // read Mode

  if (MyFile.is_open())
  {
    string Line;
    stUser User;

    // Read each line in the file and convert to user record
    while (getline(MyFile, Line))
    {
      User = ConvertUserLinetoRecord(Line);
      vUsers.push_back(User);
    }

    MyFile.close();
  }

  return vUsers;
}

// Function to load client data from file into a vector
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

// Function to print a line of client record
void PrintClientRecordLine(sClient Client)
{
  cout << "| " << setw(15) << left << Client.AccountNumber;
  cout << "| " << setw(10) << left << Client.PinCode;
  cout << "| " << setw(40) << left << Client.Name;
  cout << "| " << setw(12) << left << Client.Phone;
  cout << "| " << setw(12) << left << Client.AccountBalance;
}

// Function to print a line of user record
void PrintUserRecordLine(stUser User)
{
  cout << "| " << setw(15) << left << User.UserName;
  cout << "| " << setw(10) << left << User.Password;
  cout << "| " << setw(40) << left << User.Permissions;
}

// Function to print a line of client record with balance
void PrintClientRecordBalanceLine(sClient Client)
{
  cout << "| " << setw(15) << left << Client.AccountNumber;
  cout << "| " << setw(40) << left << Client.Name;
  cout << "| " << setw(12) << left << Client.AccountBalance;
}

// Function to display an access denied message
void ShowAccessDeniedMessage()
{
  cout << "\n------------------------------------\n";
  cout << "Access Denied, \nYou don't Have Permission To Do this,\nPlease Contact Your Admin.";
  cout << "\n------------------------------------\n";
}

// Function to show all clients in the system
void ShowAllClientsScreen()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
  {
    ShowAccessDeniedMessage();
    return;
  }

  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

  // Display client list in a formatted table
  cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  // Display table headers
  cout << "| " << left << setw(15) << "Account Number";
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
      // Print each client record line
      PrintClientRecordLine(Client);
      cout << endl;
    }

  // Display table footer
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
}

// ... (Continue the rest of the code)

// Function to show all users in the system
void ShowAllUsersScreen()
{
  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

  // Display user list in a formatted table
  cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  // Display table headers
  cout << "| " << left << setw(15) << "User Name";
  cout << "| " << left << setw(10) << "Password";
  cout << "| " << left << setw(40) << "Permissions";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  if (vUsers.size() == 0)
    cout << "\t\t\t\tNo Users Available In the System!";
  else
    for (stUser User : vUsers)
    {
      // Print each user record line
      PrintUserRecordLine(User);
      cout << endl;
    }

  // Display table footer
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
}

// Function to show total balances of all clients
void ShowTotalBalances()
{
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

  // Display balances list in a formatted table
  cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;

  // Display table headers
  cout << "| " << left << setw(15) << "Account Number";
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
      // Print each client record balance line
      PrintClientRecordBalanceLine(Client);
      TotalBalances += Client.AccountBalance;
      cout << endl;
    }

  // Display table footer with total balances
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n"
       << endl;
  cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}

// Function to print client details
void PrintClientCard(sClient Client)
{
  cout << "\nThe following are the client details:\n";
  cout << "-----------------------------------";
  cout << "\nAccount Number: " << Client.AccountNumber;
  cout << "\nPin Code     : " << Client.PinCode;
  cout << "\nName         : " << Client.Name;
  cout << "\nPhone        : " << Client.Phone;
  cout << "\nAccount Balance: " << Client.AccountBalance;
  cout << "\n-----------------------------------\n";
}

// Function to print user details
void PrintUserCard(stUser User)
{
  cout << "\nThe following are the user details:\n";
  cout << "-----------------------------------";
  cout << "\nUsername    : " << User.UserName;
  cout << "\nPassword    : " << User.Password;
  cout << "\nPermissions : " << User.Permissions;
  cout << "\n-----------------------------------\n";
}

// Function to find a client by account number
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

// Function to find a user by username
bool FindUserByUsername(string Username, vector<stUser> vUsers, stUser &User)
{
  for (stUser U : vUsers)
  {
    if (U.UserName == Username)
    {
      User = U;
      return true;
    }
  }
  return false;
}

// Function to find a user by username and password
bool FindUserByUsernameAndPassword(string Username, string Password, stUser &User)
{
  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

  for (stUser U : vUsers)
  {
    if (U.UserName == Username && U.Password == Password)
    {
      User = U;
      return true;
    }
  }
  return false;
}

// Function to change client record details
sClient ChangeClientRecord(string AccountNumber)
{
  sClient Client;
  Client.AccountNumber = AccountNumber;

  // Prompt for and update PinCode, Name, Phone, and AccountBalance
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

// Function to change user record details
stUser ChangeUserRecord(string Username)
{
  stUser User;
  User.UserName = Username;

  // Prompt for and update Password and Permissions
  cout << "\n\nEnter Password? ";
  getline(cin >> ws, User.Password);

  User.Permissions = ReadPermissionsToSet();

  return User;
}

// Function to mark a client for deletion by account number
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

// Function to mark a user for deletion by username
bool MarkUserForDeleteByUsername(string Username, vector<stUser> &vUsers)
{
  for (stUser &U : vUsers)
  {
    if (U.UserName == Username)
    {
      U.MarkForDelete = true;
      return true;
    }
  }
  return false;
}

// Function to save client data to file and exclude marked records
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

// Function to save user data to file and exclude marked records
vector<stUser> SaveUsersDataToFile(string FileName, vector<stUser> vUsers)
{
  fstream MyFile;
  MyFile.open(FileName, ios::out); // overwrite
  string DataLine;

  if (MyFile.is_open())
  {
    for (stUser U : vUsers)
    {
      if (!U.MarkForDelete)
      {
        // Write records that are not marked for delete
        DataLine = ConvertUserRecordToLine(U);
        MyFile << DataLine << endl;
      }
    }

    MyFile.close();
  }

  return vUsers;
}

// Function to add a data line to a file
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

// Function to add a new client
void AddNewClient()
{
  sClient Client;
  Client = ReadNewClient();
  AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

// Function to add a new user
void AddNewUser()
{
  stUser User;
  User = ReadNewUser();
  AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

// Function to add new clients in a loop
void AddNewClients()
{
  char AddMore = 'Y';

  do
  {
    cout << "Adding New Client:\n\n";
    AddNewClient();
    cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
    cin >> AddMore;
  } while (toupper(AddMore) == 'Y');
}

// Function to add new users in a loop
void AddNewUsers()
{
  char AddMore = 'Y';

  do
  {
    cout << "Adding New User:\n\n";
    AddNewUser();
    cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
    cin >> AddMore;
  } while (toupper(AddMore) == 'Y');
}

// Function to delete a client by account number
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
  sClient Client;
  char Answer = 'n';

  if (FindClientByAccountNumber(AccountNumber, vClients, Client))
  {
    PrintClientCard(Client);
    cout << "\n\nAre you sure you want to delete this client? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
      MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
      SaveCleintsDataToFile(ClientsFileName, vClients);
      // Refresh clients
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
}

// Function to delete a user by username
bool DeleteUserByUsername(string Username, vector<stUser> &vUsers)
{
  if (Username == "Admin")
  {
    cout << "\n\nYou cannot delete this User.";
    return false;
  }

  stUser User;
  char Answer = 'n';

  if (FindUserByUsername(Username, vUsers, User))
  {
    PrintUserCard(User);
    cout << "\n\nAre you sure you want to delete this User? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
      MarkUserForDeleteByUsername(Username, vUsers);
      SaveUsersDataToFile(UsersFileName, vUsers);
      // Refresh users
      vUsers = LoadUsersDataFromFile(UsersFileName);
      cout << "\n\nUser Deleted Successfully.";
      return true;
    }
  }
  else
  {
    cout << "\nUser with Username (" << Username << ") is Not Found!";
    return false;
  }
}

// Function to update a client by account number
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
  sClient Client;
  char Answer = 'n';

  if (FindClientByAccountNumber(AccountNumber, vClients, Client))
  {
    PrintClientCard(Client);
    cout << "\n\nAre you sure you want to update this client? y/n ? ";
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
}

// Function to update user by username
bool UpdateUserByUsername(string Username, vector<stUser> &vUsers)
{
  stUser User;
  char Answer = 'n';

  if (FindUserByUsername(Username, vUsers, User))
  {
    PrintUserCard(User);
    cout << "\n\nAre you sure you want to update this User? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
      for (stUser &U : vUsers)
      {
        if (U.UserName == Username)
        {
          U = ChangeUserRecord(Username);
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
    cout << "\nUser with Username (" << Username << ") is Not Found!";
    return false;
  }
}

// Function to deposit balance to client by account number
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
        SaveCleintsDataToFile(ClientsFileName, vClients);
        cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
        return true;
      }
    }
    return false;
  }
  return false;
}

// Function to read client account number
string ReadClientAccountNumber()
{
  string AccountNumber = "";
  cout << "\nPlease enter AccountNumber? ";
  cin >> AccountNumber;
  return AccountNumber;
}

// Function to read username
string ReadUserName()
{
  string Username = "";
  cout << "\nPlease enter Username? ";
  cin >> Username;
  return Username;
}

// Function to show the list of users screen
void ShowListUsersScreen()
{
  ShowAllUsersScreen();
}

// Function to show the add new user screen
void ShowAddNewUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tAdd New User Screen";
  cout << "\n-----------------------------------\n";
  AddNewUsers();
}

// Function to show the delete user screen
void ShowDeleteUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tDelete Users Screen";
  cout << "\n-----------------------------------\n";
  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
  string Username = ReadUserName();
  DeleteUserByUsername(Username, vUsers);
}

// Function to show the update user screen
void ShowUpdateUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tUpdate Users Screen";
  cout << "\n-----------------------------------\n";
  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
  string Username = ReadUserName();
  UpdateUserByUsername(Username, vUsers);
}

// Function to show the delete client screen
void ShowDeleteClientScreen()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
  {
    ShowAccessDeniedMessage();
    return;
  }

  cout << "\n-----------------------------------\n";
  cout << "\tDelete Client Screen";
  cout << "\n-----------------------------------\n";
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  string AccountNumber = ReadClientAccountNumber();
  DeleteClientByAccountNumber(AccountNumber, vClients);
}

// Function to show the update client screen
void ShowUpdateClientScreen()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
  {
    ShowAccessDeniedMessage();
    return;
  }

  cout << "\n-----------------------------------\n";
  cout << "\tUpdate Client Info Screen";
  cout << "\n-----------------------------------\n";
  vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
  string AccountNumber = ReadClientAccountNumber();
  UpdateClientByAccountNumber(AccountNumber, vClients);
}

// Function to show the add new clients screen
void ShowAddNewClientsScreen()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
  {
    ShowAccessDeniedMessage();
    return;
  }

  cout << "\n-----------------------------------\n";
  cout << "\tAdd New Clients Screen";
  cout << "\n-----------------------------------\n";
  AddNewClients();
}

// Function to show the find client screen
void ShowFindClientScreen()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
  {
    ShowAccessDeniedMessage();
    return;
  }

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

// Function to show the find user screen
void ShowFindUserScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tFind User Screen";
  cout << "\n-----------------------------------\n";
  vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
  stUser User;
  string Username = ReadUserName();
  if (FindUserByUsername(Username, vUsers, User))
    PrintUserCard(User);
  else
    cout << "\nUser with Username [" << Username << "] is not found!";
}

// Function to show the end screen
void ShowEndScreen()
{
  cout << "\n-----------------------------------\n";
  cout << "\tProgram Ends :-)";
  cout << "\n-----------------------------------\n";
}

// Function to show the deposit screen
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

// Continue with the rest of the code...
// Function to show the withdraw screen
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

  // Validate that the amount does not exceed the balance
  while (Amount > Client.AccountBalance)
  {
    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
    cout << "Please enter another amount? ";
    cin >> Amount;
  }

  DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

// Function to show the total balances screen
void ShowTotalBalancesScreen()
{
  ShowTotalBalances();
}

// Function to check access permission
bool CheckAccessPermission(enMainMenuePermissions Permission)
{
  if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
    return true;
  if ((Permission & CurrentUser.Permissions) == Permission)
    return true;
  else
    return false;
}

// Function to go back to the main menu
void GoBackToMainMenue()
{
  cout << "\n\nPress any key to go back to Main Menu...";
  system("pause>0");
  ShowMainMenue();
}

// Function to go back to the transactions menu
void GoBackToTransactionsMenue()
{
  cout << "\n\nPress any key to go back to Transactions Menu...";
  system("pause>0");
  ShowTransactionsMenue();
}

// Function to go back to the manage users menu
void GoBackToManageUsersMenue()
{
  cout << "\n\nPress any key to go back to Manage Users Menu...";
  system("pause>0");
  ShowManageUsersMenue();
}

// Function to read transactions menu option
short ReadTransactionsMenueOption()
{
  cout << "Choose what do you want to do? [1 to 4]? ";
  short Choice = 0;
  cin >> Choice;
  return Choice;
}

// Function to perform transactions menu option
void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
  switch (TransactionMenueOption)
  {
  case enTransactionsMenueOptions::eDeposit:
  {
    system("cls");
    ShowDepositScreen();
    GoBackToTransactionsMenue();
    break;
  }
  case enTransactionsMenueOptions::eWithdraw:
  {
    system("cls");
    ShowWithDrawScreen();
    GoBackToTransactionsMenue();
    break;
  }
  case enTransactionsMenueOptions::eShowTotalBalance:
  {
    system("cls");
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

// Function to show transactions menu
void ShowTransactionsMenue()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
  {
    ShowAccessDeniedMessage();
    GoBackToMainMenue();
    return;
  }

  system("cls");
  cout << "===========================================\n";
  cout << "\t\tTransactions Menu Screen\n";
  cout << "===========================================\n";
  cout << "\t[1] Deposit.\n";
  cout << "\t[2] Withdraw.\n";
  cout << "\t[3] Total Balances.\n";
  cout << "\t[4] Main Menu.\n";
  cout << "===========================================\n";

  PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

// Function to read main menu option
short ReadMainMenueOption()
{
  cout << "Choose what do you want to do? [1 to 8]? ";
  short Choice = 0;
  cin >> Choice;
  return Choice;
}

// Function to perform manage users menu option
void PerfromManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
{
  switch (ManageUsersMenueOption)
  {
  case enManageUsersMenueOptions::eListUsers:
  {
    system("cls");
    ShowListUsersScreen();
    GoBackToManageUsersMenue();
    break;
  }
  case enManageUsersMenueOptions::eAddNewUser:
  {
    system("cls");
    ShowAddNewUserScreen();
    GoBackToManageUsersMenue();
    break;
  }
  case enManageUsersMenueOptions::eDeleteUser:
  {
    system("cls");
    ShowDeleteUserScreen();
    GoBackToManageUsersMenue();
    break;
  }
  case enManageUsersMenueOptions::eUpdateUser:
  {
    system("cls");
    ShowUpdateUserScreen();
    GoBackToManageUsersMenue();
    break;
  }
  case enManageUsersMenueOptions::eFindUser:
  {
    system("cls");
    ShowFindUserScreen();
    GoBackToManageUsersMenue();
    break;
  }
  case enManageUsersMenueOptions::eMainMenue:
  {
    ShowMainMenue();
  }
  }
}

// Function to read manage users menu option
short ReadManageUsersMenueOption()
{
  cout << "Choose what do you want to do? [1 to 6]? ";
  short Choice = 0;
  cin >> Choice;
  return Choice;
}

// Function to show manage users menu
void ShowManageUsersMenue()
{
  if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
  {
    ShowAccessDeniedMessage();
    GoBackToMainMenue();
    return;
  }

  system("cls");
  cout << "===========================================\n";
  cout << "\t\tManage Users Menu Screen\n";
  cout << "===========================================\n";
  cout << "\t[1] List Users.\n";
  cout << "\t[2] Add New User.\n";
  cout << "\t[3] Delete User.\n";
  cout << "\t[4] Update User.\n";
  cout << "\t[5] Find User.\n";
  cout << "\t[6] Main Menu.\n";
  cout << "===========================================\n";

  PerfromManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
}

// Function to perform main menu option
// Function to perform main menu option
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
  switch (MainMenueOption)
  {
  case enMainMenueOptions::eListClients:
  {
    system("cls");
    ShowAllClientsScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eAddNewClient:
  {
    system("cls");
    ShowAddNewClientsScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eDeleteClient:
  {
    system("cls");
    ShowDeleteClientScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eUpdateClient:
  {
    system("cls");
    ShowUpdateClientScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eFindClient:
  {
    system("cls");
    ShowFindClientScreen();
    GoBackToMainMenue();
    break;
  }
  case enMainMenueOptions::eShowTransactionsMenue:
  {
    system("cls");
    ShowTransactionsMenue();
    break;
  }
  case enMainMenueOptions::eManageUsers:
  {
    system("cls");
    ShowManageUsersMenue();
    break;
  }
  case enMainMenueOptions::eExit:
  {
    system("cls");
    // ShowEndScreen();
    Login();
    break;
  }
  }
}

// Function to show the main menu
void ShowMainMenue()
{
  system("cls");
  cout << "===========================================\n";
  cout << "\t\tMain Menu Screen\n";
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

// Function to load user information for login
bool LoadUserInfo(string Username, string Password)
{
  if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
    return true;
  else
    return false;
}

// Function for user login
void Login()
{
  bool LoginFaild = false;
  string Username, Password;

  do
  {
    system("cls");
    cout << "\n---------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n---------------------------------\n";

    if (LoginFaild)
    {
      cout << "Invalid Username/Password!\n";
    }

    cout << "Enter Username? ";
    cin >> Username;
    cout << "Enter Password? ";
    cin >> Password;

    LoginFaild = !LoadUserInfo(Username, Password);

  } while (LoginFaild);

  ShowMainMenue();
}

// Main function
int main()
{
  Login();
  system("pause>0");
  return 0;
}
