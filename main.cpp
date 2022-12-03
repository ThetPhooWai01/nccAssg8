#include <iostream>
#include "Bank.h"
using namespace std;

int main()
{
    Bank myBank;
    myBank.userDataLoading();
    myBank.transferListLoading();
    myBank.mainMenu();

    return 0;
}
