#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string sep = "#//#";
struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool markForDelete = false;
};
void Application (vector<sClient> & vClients);
vector<string> SplitString(string S1, string Delim) {
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (sWord != "") {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "") {
        vString.push_back(S1);
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
    sClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stoi(vClientData[4]);
    return Client;
}
vector<sClient> LoadCleintsDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            sClient Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
short ReadChoice() {
    short number = 0;
    do {
        cout << "Choose What do you Want ?[1-6] \n";
        cin >> number;
    }while(number >= 7 || number <= 0);
    return number;
}

void showMainMenu() {
    cout << "===================================================\n";
    cout << left<<setw(17)<<"Main Menu Screen\n";
    cout << "===================================================\n\n";
    cout<< left <<setw(10)<<"[1] Show Clients List\n";
    cout<< left <<setw(10)<<"[2] Add New Client.\n";
    cout<< left <<setw(10)<<"[3] Delete Client.\n";
    cout<< left <<setw(10)<<"[4] Update Client Info.\n";
    cout<< left <<setw(10)<<"[5] Find Client.\n";
    cout<< left <<setw(10)<<"[6] Exit.\n";

}
void PrintClientRecord(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintAllClientsData(vector <sClient> vClients) {
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients) {
        PrintClientRecord(Client);
        cout << endl;
    }     cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void backtoMainMenu() {
    string key;
    cout << "\n\n press any charcter to back to main menu ...";
    cin >> key;
}
string convertRecordToline(sClient data,string sep) {
    string String = "";
    String += data.AccountNumber + sep;
    String += data.PinCode + sep;
    String += data.Name + sep;
    String += data.Phone + sep;
    String += to_string(data.AccountBalance);
    return String;
}
void saveStringDataToFileAndClear(string fileName,string String) {
    fstream File;
    File.open(fileName,ios::out|ios::app);
    if(File.is_open()) {
        File<<String;
        File<<endl;
        File.close();
    }
}
bool findClient(vector <sClient> vClients,string accountNumber) {
    for(sClient & client : vClients) {
        if(client.AccountNumber == accountNumber) {
            PrintClientRecord(client);
            return true;
        }
    }
    return false;
}
void saveVectorToFile(vector<sClient> clients) {
    for(sClient &client:clients) {
        saveStringDataToFileAndClear(ClientsFileName,convertRecordToline(client,sep));
    }
}

void appendClientToFile(sClient client,string fileName) {
    fstream File;
    string String = convertRecordToline(client,sep);
    File.open(fileName,ios::out|ios::app);
    if(File.is_open()) {
        File<<String;
        File<<endl;
    }
}
sClient ReaddNewClient(vector<sClient> vclients) {
    sClient data;
    cout << "Account number : ";
    getline(cin>>ws,data.AccountNumber);
    while(findClient(vclients,data.AccountNumber)) {
        cout << "\n\nThis number is take please reWrite new Account number";
        getline(cin>>ws,data.AccountNumber);
    }
    cout << "Pin code : ";
    getline(cin,data.PinCode);

    cout<< "Name : ";
    getline(cin,data.Name);

    cout << "phone : ";
    getline(cin,data.Phone);

    cout << "balance: ";
    cin>> data.AccountBalance;
    return data;
}

sClient addNewClientsToVectorandReturnIt(vector<sClient> &vclients) {
    sClient client;
    client = ReaddNewClient(vclients);
    vclients.push_back(client);
    return client;
}

void addNewClients(vector<sClient>& vClients) {
    sClient client;
    char ask = 'y';
    do {
        client = addNewClientsToVectorandReturnIt(vClients);
        appendClientToFile(client,ClientsFileName);
        cout << "Client added successfuly , do you want to add more Y/N? ";
        cin >> ask;
    }while(tolower(ask) == 'y');
}

void caseSelected(vector<sClient>& vClients,int choice) {

    switch (choice) {
        case 1:
            PrintAllClientsData(vClients);
            backtoMainMenu();
            Application(vClients);
            break;
        case 2:
            addNewClients(vClients);
            backtoMainMenu();
            Application(vClients);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
    }
}
void Application (vector<sClient> & vClients) {
    showMainMenu();
    short choose = ReadChoice();
    caseSelected(vClients,choose);
}



int main() {
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    Application(vClients);

    return 0;
}