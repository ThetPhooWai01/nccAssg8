#ifndef BANK_H
#define BANK_H
#include "iostream"
using namespace std;
class Bank
{
    public:

        string name[100];
        string password[100];
        string amount[100];
        string tName[100];
        string rName[100];
        string tAmount[100];
        string tTime[100];
        int userIndex = 0;
        int currentIndex = 0;
        int transferIndex = 0;

        void userRegister();
        void userLogin();
        void mainMenu();
        void userDataLoading();
        int nameChecking(string cname);
        void profile();
        void exchange();
        void userDataSaving();
        void transfer();
        void withdraw();
        void recharge();
        void transferList();
        void transferListSaving();
        void transferListLoading();
};

#endif // BANK_H

