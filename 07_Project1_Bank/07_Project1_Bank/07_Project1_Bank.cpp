

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string FileName = "Clients.txt";

struct stClient {

    string AccountNum;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance=0.0;
    bool MarkForDelete = false;

};

vector <string> SplitFunction(string s1, string delim = "#//#") {

    vector <string> Vstring;
    string word = "";
    short pos=0;

    while ((pos = s1.find(delim)) != std::string::npos) {

        word = s1.substr(0, pos);

        if (word != "") {

            Vstring.push_back(word);
        }

        s1.erase(0,pos + delim.length());
    }

    if (s1 != "") {

        Vstring.push_back(s1);
    }

    return Vstring;
}

stClient ConvertLineToRecord(string s1,string delim = "#//#") {

    vector <string> Vstring = SplitFunction(s1, delim= "#//#");
    stClient sClient;

    sClient.AccountNum = Vstring[0];
    sClient.PinCode = Vstring[1];
    sClient.Name = Vstring[2];
    sClient.Phone = Vstring[3];
    sClient.AccountBalance = stod(Vstring[4]);
    
    return sClient;

}

vector <stClient> ConvertFileToVector(string FileName) {

    fstream Myfile;

    vector <stClient> vClient;

    Myfile.open(FileName, ios::in);

    if (Myfile.is_open()) {

        string line;
        stClient sClient;

        while (getline(Myfile, line)) {

            sClient = ConvertLineToRecord(line);
            vClient.push_back(sClient);

        }
    }
    return vClient;
}

void PrintClient(stClient sClient) {

    cout << "| " << setw(15)  << left <<sClient.AccountNum;
    cout << "| " << setw(10) << left << sClient.PinCode;
    cout << "| " << setw(40) << left <<sClient.Name;
    cout << "| " << setw(12) << left << sClient.Phone;
    cout << "| " << setw(12) << left <<sClient.AccountBalance;

}

void PrintAllClient() {

    vector <stClient> vClient = ConvertFileToVector(FileName);

    for (stClient C : vClient) {

        PrintClient(C);
        cout << endl;
    }
}

stClient ReadNewClient() {

    stClient sClient;

    cout << "Enter Your AccountNum ? ";
    getline(cin >> ws, sClient.AccountNum);
    
    cout << "Enter Your PinCode ? ";
    getline(cin, sClient.PinCode);

    cout << "Enter Your Name ? ";
    getline(cin, sClient.Name);

    cout << "Enter Your Phone ? ";
    getline(cin, sClient.Phone);

    cout << "Enter Your AccountBalance ? ";
    cin >> sClient.AccountBalance;

    return sClient;

}

string ConvertRecordToLine(stClient &sClient,string delim = "#//#") {

    string s1;

    s1 += sClient.AccountNum + delim;
    s1 += sClient.PinCode + delim;
    s1 += sClient.Name + delim;
    s1 += sClient.Phone + delim;
    s1 += to_string(sClient.AccountBalance);

    return s1;

}

void SaveDataToClientFile(string FileName, string DataLine) {

    fstream MyFile;

    MyFile.open(FileName,ios::out | ios::app);

    if (MyFile.is_open()) {

        MyFile << DataLine << endl;

        MyFile.close();
    }

}

stClient ChangeClientData() {

    stClient sClient;

    cout << "Enter Account Number " << endl;
    getline(cin >> ws, sClient.AccountNum);

    cout << "Enter PIN Number " << endl;
    getline(cin, sClient.PinCode);

    cout << "Enter Your Name " << endl;
    getline(cin >> ws, sClient.Name);

    cout << "Enter Phone Number " << endl;
    getline(cin >> ws, sClient.Phone);

    cout << "Enter Account Balance " << endl;
    cin >> sClient.AccountBalance;

    return sClient;

}

void AddClient() {

    stClient sClient = ReadNewClient();

    SaveDataToClientFile(FileName, ConvertRecordToLine(sClient));

}

void AddNewClient() {

    char AddNew;

    do {

        cout << "Add New Client Please: \n\n";

        AddClient();

        cout << "New Client AddSuccessfuly, Want To Add new Client \n";
        cin >> AddNew;

    } while (toupper(AddNew) == ' Y ');

}

bool FindClientByAccountNum(string accountNum, vector <stClient> Vclient, stClient &sClient) {


    for (stClient C: Vclient) {

        if (accountNum == C.AccountNum) {

            sClient = C;
            PrintClient(sClient);
            return true;
        }
        
    }

    return false;
}

bool MarkToDelete(string AccountNum, vector <stClient> &Vclient) {

    for (stClient &C : Vclient) {

        if (AccountNum == C.AccountNum) {

            C.MarkForDelete = true;
            
        }
    }

    return false;

}

vector <stClient> LoadClientDataToFile(string FileName,vector <stClient> Vclient) {

    fstream Myfile;

    Myfile.open(FileName, ios :: out);

    if (Myfile.is_open()) {
            
        string Line;

        for (stClient& C : Vclient) {

            if (C.MarkForDelete == false) {

                Line = ConvertRecordToLine(C);
                Myfile << Line << endl;
            }
        }
        Myfile.close();
    }
    return Vclient;

}

bool DeleteClientByMarkdelete(string AccountNum, vector <stClient> &Vclient) {

    char X = 'n';
    stClient sClient;

    if(FindClientByAccountNum(AccountNum, Vclient, sClient)) {


        cout << "\nAre you sure want to delete this client ? Y/N ";
        cin >> X;

        if (toupper(X) == 'Y') {

            MarkToDelete(AccountNum, Vclient);
            LoadClientDataToFile(FileName, Vclient);


            cout << "\n\nClient is delete Succefuly\n";


            return true;

        }
        }
    else {

        cout << "AccountNum is not Found!\n";
        
    }
    return false;
}

bool UpdateclientByAccountNum(string AccountNum, vector <stClient> Vclient) {

    stClient sClient;
    char X = 'n';

    if (FindClientByAccountNum(AccountNum, Vclient, sClient)) {

        cout << "You Want to update this client? ";
        cin >> X;

        if (toupper(X) == 'Y') {
        
            for (stClient& C : Vclient) {

                if (C.AccountNum == AccountNum) {

                    C = ChangeClientData();

                }

            }
            LoadClientDataToFile(FileName,Vclient);

            cout << "Client is Updated Succesfuly";
            return true;
        }
    }
    else {

        cout << "Not Found this Client ! ";
        return false;
    }

}

string ReadAccountNum() {

    string AccountNum;
    cout << "Enter Account Num to Find By: ? ";
    cin >> AccountNum;

    return AccountNum;
}

void ScreenMenue() {

    short num;
    stClient sClient;
    vector <stClient> Vclient = ConvertFileToVector(FileName);
    
    cout << "\n\t\tScreen Menue\n\t\t";
    cout << "________________________\n\n";
    cout << " \t\t[1] ShowClients " << endl;
    cout << " \t\t[2] AddClietns " << endl;
    cout << " \t\t[3] FindClietnByAccountNumber " << endl;
    cout << " \t\t[4] DeleteClietnByAccountNumber " << endl;
    cout << " \t\t[5] UpdateClietnByAccountNumber " << endl;
    cin >> num;
 
        if (num == 1) {

            PrintAllClient();
            system("pause>0");
        }
        if (num == 2) {

            AddNewClient();
            system("pause>0");
        }
        if (num == 3) {

            FindClientByAccountNum(ReadAccountNum(),Vclient,sClient);
            system("pause>0");
        }
        if (num == 4) {

            DeleteClientByMarkdelete(ReadAccountNum(), Vclient);
            system("pause>0");
        }
        if (num == 5) {

            UpdateclientByAccountNum(ReadAccountNum(), Vclient);
            system("pause>0");
        }
        
       
    
}

int main()
{
    
    ScreenMenue();
}
