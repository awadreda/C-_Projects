#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
// #include <origalt.h >
using namespace std;
const string FileName = "C:/Tutourials/HadhoudAdvices/projects/project!/Bank1.txt";

enum enMenue
{
  ClientList = 1,
  AddNewBankClient = 2,
  DeleteClient = 3,
  UpdateClient = 4,
  FindClient = 5,
  Exit = 6
};

struct stClient
{
  string AccountNumber;
  string PinCode;
  string Name;
  string Phone;
  double AccountBalance;
  bool MarkForDelete = false;
};

// Add NEw Client
vector<string> SplitString(string line, string Delim = "#//#")
{
  vector<string> vString;
  short pos = 0;
  string word;
  while ((pos = line.find(Delim)) != string::npos)
  {
    word = line.substr(0, pos); // Store the word
    if (word != "")
    {
      vString.push_back(word);
    }
    line.erase(0, pos + Delim.length());
  }
  if (line != "")
  {
    vString.push_back(line);
  }
  return vString;
}

stClient FillDataFromVector(string line, string delim = "#//#")
{
  vector<string> Data;
  Data = SplitString(line, delim);
  stClient Client;
  Client.AccountNumber = Data[0];
  Client.PinCode = Data[1];
  Client.Name = Data[2];
  Client.Phone = Data[3];
  Client.AccountBalance = stod(Data[4]);
  return Client;
}

vector<stClient> ReadFormBankFile()
{
  vector<stClient> vClientsDataStruct;
  fstream MyFile;
  MyFile.open(FileName, ios::in);
  if (MyFile.is_open())
  {
    stClient client;
    string line;
    while (getline(MyFile, line))
    {
      client = FillDataFromVector(line);
      vClientsDataStruct.push_back(client);
    }
    MyFile.close();
  }
  return vClientsDataStruct;
}

void PrintClientRecord(stClient Client)
{
  cout << "|" << setw(15) << left << Client.AccountNumber;
  cout << "|" << setw(10) << left << Client.PinCode;
  cout << "|" << setw(40) << left << Client.Name;
  cout << "|" << setw(12) << left << Client.Phone;
  cout << "|" << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientSDataVector(vector<stClient> vClientsData)
{
  cout << "\n\t\t\t\t\tClients list (" << vClientsData.size() << ") Client(s).";
  cout << "\n______________________________________________";
  cout << "_____________________________________________\n"
       << endl;

  cout << "|" << setw(15) << left << "AcountNumber";
  cout << "|" << setw(10) << left << "PinCode";
  cout << "|" << setw(40) << left << "Name";
  cout << "|" << setw(12) << left << "phone";
  cout << "|" << setw(12) << left << "AcountBalance";
  cout << "\n______________________________________________";
  cout << "_____________________________________________\n"
       << endl;
  for (stClient &Client : vClientsData)
  {
    PrintClientRecord(Client);
    cout << "\n";
  }
  cout << "______________________________________________";
  cout << "_____________________________________________\n"
       << endl;
}

stClient ReadNewClient()
{
  stClient ClientData;
  cout << "Enter The Acount Number : ";
  getline(cin >> ws, ClientData.AccountNumber);
  cout << "Enter The Pin Code  : ";
  getline(cin, ClientData.PinCode);
  cout << "Enter Name          : ";
  getline(cin, ClientData.Name);
  cout << "Enter Phone         : ";
  getline(cin, ClientData.Phone);
  cout << "Enter Acount Balance: ";
  cin >> ClientData.AccountBalance;
  return ClientData;
}

string ConvertRecordToLine(stClient Client, string seperator = "#//#")
{
  string line = "";
  line += Client.AccountNumber + seperator;
  line += Client.PinCode + seperator;
  line += Client.Name + seperator;
  line += Client.Phone + seperator;
  line += to_string(Client.AccountBalance) + seperator;
  return line;
}

void addLineToBankflie(string line)
{
  fstream ClientsFile;
  ClientsFile.open(FileName, ios::out | ios::app);
  if (ClientsFile.is_open())
  {
    ClientsFile << line << "\n";
    ClientsFile.close();
  }
}

void NEWCLient()
{
  stClient Client;
  Client = ReadNewClient();
  addLineToBankflie(ConvertRecordToLine(Client));
}

void AddBankClients()
{
  char DoMore = 'y';
  while (toupper(DoMore) == 'Y')
  {
    cout << "Add New Client :\n\n";
    // NEWCLient();
    stClient Client;
    Client = ReadNewClient();
    addLineToBankflie(ConvertRecordToLine(Client));
    cout << "Clinet Added Successfully,do you want to add more clients ?";
    cin >> DoMore;
  }
}

// Find a Client
string Readstring(string message)
{
  string num;
  cout << message << "\n";

  getline(cin >> ws, num);
  return num;
}

void PrintClient(stClient Client)
{
  cout << "Acount Number : " << Client.AccountNumber << "\n";
  cout << "Pin Code      : " << Client.PinCode << "\n";
  cout << "Name          : " << Client.Name << "\n";
  cout << "Phone         : " << Client.Phone << "\n";
  cout << "Acount Balance: " << Client.AccountBalance << "\n";
}

bool FindClientFromVector(stClient &Client, string AcountNumber)
{

  vector<stClient> vClients;
  vClients = ReadFormBankFile();
  for (stClient c : vClients)

  {
    if (c.AccountNumber == AcountNumber)
    {
      Client = c;
      return true;
    }
  }
  return false;
}

void ShowTheFoundClient()
{
  string AcountNumber = Readstring("Enter The Account Number \n");
  stClient Client;
  if (FindClientFromVector(Client, AcountNumber))
  {
    PrintClient(Client);
  }
  else
  {
    cout << "Client With Acount Number (" << AcountNumber << ") Not Found !\n";
  }
}
// Delete Client============

bool MarkClientForDelete(string AccountNumber, vector<stClient> &vClients)
{
  for (stClient &C : vClients)
  {
    if (C.AccountNumber == AccountNumber)
    {
      C.MarkForDelete = true;
      return true;
    }
  }
  return false;
}

vector<stClient> SaveClientsDataToFile(vector<stClient> vClients)
{
  fstream MyFile;
  MyFile.open(FileName, ios::out);
  string DataLine;
  if (MyFile.is_open())
  {
    for (stClient C : vClients)
    {
      if (C.MarkForDelete == false)
      {
        DataLine = ConvertRecordToLine(C);
        MyFile << DataLine << "\n";
      }
    }
    MyFile.close();
  }
  else
  {
    cout << "the File didn't Open in Function SaveClientsDataToFile \n";
  }
  return vClients;
}

bool DeleteClientByAccountNumber(vector<stClient> &vClients)
{
  string AccountNumber = Readstring("Enter The Account Number you Want To delete\n");
  stClient Client;
  char Answer = 'n';
  if (FindClientFromVector(Client, AccountNumber))
  {
    PrintClient(Client);
    cout << "\n\nAre You sure you want delete this client ?y/n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
      MarkClientForDelete(AccountNumber, vClients);
      SaveClientsDataToFile(vClients);
      // Refreesh Clients
      vClients = ReadFormBankFile();

      cout << "\n\nClient Deleted Successfully.";
      return true;
    }
  }
  else
  {
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found !";
  }
  return false;
}

// Update client
stClient ChangeClientRecord(string AccountNumber)
{
  stClient Client;
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

bool UpdateClientByAccountNumber(vector<stClient> &vClients)
{
  string AccountNumber = Readstring("Enter the Account Number ot update\n");
  stClient Client;
  char Answer = 'n';

  if (FindClientFromVector(Client, AccountNumber))
  {
    PrintClient(Client);
    cout << "\n\nAre you sure you want to update this client? (y/n): ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
      for (stClient &C : vClients)
      {
        if (C.AccountNumber == AccountNumber)
        {
          C = ChangeClientRecord(AccountNumber);
          break;
        }
      }

      SaveClientsDataToFile(vClients);
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

//=============The Bank ============
void PrintMenue()
{
  cout << "\n======================================================\n";
  cout << "\n\t\t\tMain Menue Screen\t\t\t\n";
  cout << "\n======================================================\n";
  cout << "[1] Show Client List.\n";
  cout << "[2] Add New Client.\n";
  cout << "[3] Delete Client.\n";
  cout << "[4] Update Client.\n";
  cout << " [5] Find  Client.\n";
  cout << "[6] Exit.";
  cout << "\n======================================================\n";
  cout << "Choose What do want to do ?[1 to 6]\n";
}

void MainChoice(enMenue Choice, vector<stClient> &vClients)
{
  switch (Choice)
  {
  case enMenue::ClientList:
  {
    PrintAllClientSDataVector(vClients);
    break;
  }
  case enMenue::AddNewBankClient:
  {
    AddBankClients();
  }
  case enMenue::FindClient:
  {
    ShowTheFoundClient();
  }
  case enMenue::DeleteClient:
  {
    DeleteClientByAccountNumber(vClients);
  }
  case enMenue::UpdateClient:
  {
    UpdateClientByAccountNumber(vClients);
  }
  case enMenue::Exit:
  {
    // system("pause>0");
  }
  default:
  {
    PrintAllClientSDataVector(vClients);
  }
  break;
  }
}

void MainMenue()
{
  vector<stClient> vClients = ReadFormBankFile();

  PrintMenue();
  short Choice;
  cin >> Choice;
  MainChoice(enMenue(Choice), vClients);
}

int main()
{
  MainMenue();
  return 0;
}