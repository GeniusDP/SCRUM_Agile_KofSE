#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "DataBase.h"
#include "Printer.h"
#include "User.h"
#include "Course.h"

using namespace std;

class System {
	DataBase dataBase;
	Printer printer;
	User user;
public:
	System(){	
		setlocale(LC_ALL, "ukr");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
			int response = printer.Welcom();//0 - register, 1 - login
			if (!response) {
				//registration
				user = printer.Registration();
				dataBase.makeNewUser(user);
			}
			else {
				//logging in
				bool haveFound;
				do{
					user = printer.Login();
					haveFound = dataBase.foundUser(user);
					if (haveFound)cout << "Hello!\n";
					else cout << "We don`t have such user\n";
					system("pause");
				} while (!haveFound);
				printer.goIntoUserCabinet(user);
			}
	}
};