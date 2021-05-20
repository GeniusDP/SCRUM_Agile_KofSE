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
		
			int response = printer.Welcom();//0 - register, 1 - login
			if (!response) {
				//registration
				user = printer.Registration();
				dataBase.makeNewUser(user);
			}
			else {
				//logging in
				do{
					user = printer.Login();
				} while (!dataBase.foundUser(user));
			}
	}

};