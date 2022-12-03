#include "iostream"
#include "string"
#include "fstream"
#include "time.h"
#include "Bank.h"
using namespace std;

void Bank::mainMenu(){
    string option;
    cout<<"Welcome to bank!"<<endl;
    cout<<"Press 1 to register\nPress 2 to login\nPress 3 to exit : "<<endl;
    cin>>option;
    if(option == "1"){
        userRegister();
    }else if(option == "2"){
        userLogin();
    }else if(option == "3"){
        cout<<"Bye Bye,Good Luck"<<endl;
        userDataSaving();
        transferListSaving();
        exit(1);
    }
    else{
        cout<<"Invalid Input!"<<endl;
        mainMenu();
    }

}
void Bank::userRegister(){
    string cname;
    string pass;
    string cpass;
    int camount;
    cout<<"This is register."<<endl;
    cout<<"Enter your name : ";
    cin>>cname;
    int check = nameChecking(cname);
    if(check != -1){
        cout<<"Name already exists. Please use another name."<<endl;
        userRegister();
    }else{
        while(1){
            cout<<"Enter your password : ";
            cin>>pass;
            cout<<"Confirm your password : ";
            cin>>cpass;
            if(pass == cpass){
                while(1){
                    cout<<"Minimum amount is 1000.Enter you amount : ";
                    cin>>camount;
                    if(camount < 1000){
                        cout<<"Please enter valid amount."<<endl;
                    }else{
                        name[userIndex] = cname;
                        password[userIndex] = pass;
                        amount[userIndex] = to_string(camount);
                        userIndex++;
                        cout<<"Registration success.Please login."<<endl;
                        userLogin();
                    }
                }
            }else{
                cout<<"Passwords do not match."<<endl;
            }
        }
    }
}
void Bank::userLogin(){
    string cname;
    string cpass;
    int attempt = 3;
    cout<<"This is login."<<endl;
    cout<<"Enter your name to login : ";
    cin>>cname;
    int check = nameChecking(cname);
    if(check == -1){
        cout<<"Name does not exist."<<endl;
        userLogin();
    }else{
        while(1){
            cout<<"Enter your password to login : ";
            cin>>cpass;
            if(password[check] == cpass){
                currentIndex = check;
                profile();
                exchange();
            }else{
                if(attempt == 0){
                    cout<<"Too many attempts to login.Please try again later."<<endl;
                    mainMenu();
                }else{
                    cout<<"Incorrect password!"<<endl;
                    cout<<"You have "<<attempt<<" chances left to try."<<endl;
                    attempt--;
                }
            }
        }
    }
}
void Bank::userDataLoading(){
    int count = 0;
    string data;
    string dataLine;
    string userFile = "users.txt";
    ifstream file(userFile);
    if(!file.is_open()){
        cout<<"File cannot open!"<<endl;
        exit(1);
    }else{
        while(getline(file,dataLine)){
            dataLine = dataLine + " ";
            for(auto &ch :dataLine){
                if(ch == ' '){
                    if(count == 0){
                        name[userIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 1){
                        password[userIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 2){
                        amount[userIndex] = data;
                        data = "";
                        userIndex++;
                        count = 0;
                    }
                }else{
                    string st(1,ch);
                    data = data + st;
                }
            }
        }
    }
    file.close();
}
int Bank::nameChecking(string cname){
    for(int i=0; i<userIndex; i++){
        if(name[i] == cname){
            return i;
        }
    }
    return -1;
}
void Bank::profile(){
    cout<<"Your Name : "<<name[currentIndex]<<endl;
    cout<<"Your Password : "<<password[currentIndex]<<endl;
    cout<<"Your Amount : "<<amount[currentIndex]<<endl;
}
void Bank::exchange(){
    string choice;
    while(1){
        cout<<"Press 1 to transfer\nPress 2 to withdraw\nPress 3 to recharge\nPress 4 to view transfer list\nPress 5 to back\nPress 6 to exit : ";
        cin>>choice;
        if(choice == "1"){
            transfer();
        }else if(choice == "2"){
            withdraw();
        }else if(choice == "3"){
            recharge();
        }else if(choice == "4"){
            transferList();
        }else if(choice == "5"){
            mainMenu();
        }else if(choice == "6"){
            userDataSaving();
            transferListSaving();
            exit(1);
        }else{
            cout<<"Invalid Input!"<<endl;
        }
    }
}
void Bank::userDataSaving(){
    string filename ="users.txt";
    ofstream file;
    file.open(filename);

    if(!file.is_open()){
        cout<<"Unable to record!"<<endl;
    } else{
        for(int i=0 ; i<userIndex ; i++){
            string dataLine=name[i]+" "+password[i]+" "+amount[i]+"\n";
            file<<dataLine;
        }
    }

    file.close();
}
void Bank::transfer(){
    string receiverName;
    int myAmount = stoi(amount[currentIndex]);
    int receiverAmount = 0;
    int tamount = 0;
    cout<<"This is transfer section."<<endl;
    while(1){
        cout<<"Enter name you want to transfer : ";
        cin>>receiverName;
        int check = nameChecking(receiverName);
        if(check == -1){
            cout<<"User not found."<<endl;
        }else{
            while(1){
                cout<<"Enter amount to transfer : ";
                cin>>tamount;
                if(tamount > myAmount){
                    cout<<"Not enough amount!"<<endl;
                }else{
                    amount[currentIndex] = to_string(myAmount - tamount);
                    receiverAmount = stoi(amount[check]);
                    amount[check] = to_string(receiverAmount + tamount);

                    tName[transferIndex] = name[currentIndex];
                    rName[transferIndex] = name[check];
                    tAmount[transferIndex] = to_string(tamount);
                    cout<<"You transfered "<<tAmount[transferIndex]<<" to "<<rName[transferIndex]<<endl;

                    time_t now = time(0);
                    string cTime = ctime(&now);
                    string data;
                    for(auto &ch :cTime){
                        if(ch == ' '){
                                ch = '_';
                        }else{
                            string st(1,ch);
                            data = data + st;
                            }
                            }
                        tTime[transferIndex] = cTime;
                        transferIndex++;

                        profile();
                        exchange();
                }
            }

        }
    }
}
void Bank::withdraw(){
    int withdraw = 0;
    int myAmount = stoi(amount[currentIndex]);
    cout<<"This is withdraw section."<<endl;
    while(1){
        cout<<"Enter amount to withdraw : ";
        cin>>withdraw;
        if(withdraw > myAmount){
            cout<<"Not enough amount!"<<endl;
        }else{
            amount[currentIndex] = to_string(myAmount - withdraw);
            cout<<withdraw<<" is reduced from your account"<<endl;
            profile();
            exchange();
        }
    }
}
void Bank::recharge(){
    int rechargeAmount = 0;
    int myAmount = stoi(amount[currentIndex]);
    cout<<"This is recharge section."<<endl;
    while(1){
        cout<<"Enter amount to recharge : ";
        cin>>rechargeAmount;
        if(rechargeAmount < 1000){
            cout<<"Minimum recharge amount is 1000."<<endl;
        }else{
            amount[currentIndex] = to_string(myAmount + rechargeAmount);
            cout<<rechargeAmount<<" is added to your account"<<endl;
            profile();
            exchange();
        }
    }
}
void Bank::transferList(){
    cout<<"You can see your transfer lists here."<<endl;
    for(int i=0; i<transferIndex; i++){
        if(name[currentIndex] == tName[i] || name[currentIndex] == rName[i]){
            cout<<"From:"<<tName[i]<<" To:"<<rName[i]<<" Amount:"<<tAmount[i]<<" Time:"<<tTime[i]<<endl;
        }else{
            cout<<"There is no result."<<endl;
            exchange();
        }
    }
}
void Bank::transferListSaving(){
    string fileName = "transfers.txt";
    ofstream file;
    file.open(fileName);
    if(!file.is_open()){
        cout<<"Unable to record!"<<endl;
    } else{
        for(int i=0 ; i<transferIndex ; i++){
            string dataLine=tName[i]+" "+tAmount[i]+" "+rName[i]+" "+tTime[i]+"\n";
            file<<dataLine;
        }
    }
    file.close();
}
void Bank::transferListLoading(){
    int count = 0;
    string data;
    string dataLine;
    string fileName = "transfers.txt";
    ifstream file(fileName);
    if(!file.is_open()){
        cout<<"File cannot open!"<<endl;
        exit(1);
    }else{
        while(getline(file,dataLine)){
            dataLine = dataLine + " ";
            for(auto &ch :dataLine){
                if(ch == ' '){
                    if(count == 0){
                        tName[transferIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 1){
                        tAmount[transferIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 2){
                        rName[transferIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 3){
                        tTime[transferIndex] = data;
                        data = "";
                        transferIndex++;
                        count = 0;
                    }
                }else{
                    string st(1,ch);
                    data = data + st;
                }
            }
        }
    }
    file.close();
}
