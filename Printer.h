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



class Printer {

public:
    User Registration() {
        User user;
        cout << "Hello! This is registration form!\n";
        string typeOfUser = "none";
        do {
            cout << "Are you a teacher or a student?" << endl;
            cin >> typeOfUser;
        } while (!(typeOfUser == "teacher" || typeOfUser == "student"));

        string login;
        string password;
        cout << "Type in your login(one word):";
        cin >> login;
        cout << "Type in your password(one word):";
        cin >> password;
        cout << "Thanks for registration!\n";
        system("pause");
        system("cls");
        return User(typeOfUser, login, password);
    }
    
    User Login() {
        system("cls");
        string login, password, type;
        cout << "Hello! Let is log into system.\n";
        cout << "Enter your user-type: ";
        cin >> type;
        cout << "Enter your login: ";
        cin >> login;
        cout << "Enter your password: ";
        cin >> password;
        cout << "We have got such user!";
        return User(type, login, password);
    }

    int Welcom() {
        cout << "Hello on our system!\nDo you want to Register or Login?\n";
        string str;
        do {
            cin >> str;
        } while (!(str == "Register" || str == "Login"));
        if (str == "Register") {
            return 0;
        }
        else {
            return 1;
        }
        system("cls");
    }
};