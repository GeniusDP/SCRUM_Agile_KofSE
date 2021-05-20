#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Printer.h"

using namespace std;


//*************************************************************************
//****************************<<<MAIN>>>***********************************
//*************************************************************************
int main()
{
    Printer printer;
    printer.printLine(cout, "Hello on our system!\nDo you want to Register or Login?\n");
    string str;
    do {
        cin >> str;
    } while (!(str == "Register" || str == "Login"));
    system("cls");
    if (str == "Register") {
        printer.makeNewUser();
    }
    else {
        User user = printer.logIntoSystem();
        cout << endl; system("pause");
        user.goToUserCabinet();
    }
    return 0;
}
//*************************************************************************
//*************************************************************************


