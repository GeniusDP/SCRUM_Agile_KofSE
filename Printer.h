#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "User.h"
using namespace std;


class Printer {
    DataBase dataBase;
public:
    void printLine(ostream& out, string buffer) {
        out << buffer;
    }

    void makeNewUser() {
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

        if (typeOfUser == "teacher") {
            //create new teacher
            ofstream out("Database\\users.txt", ios_base::app), teacherFile("Database\\" + login + ".txt");
            Printer newPrinter;
            newPrinter.printLine(out, typeOfUser + " " + login + " " + password);
        }
        else {
            //create new student
            ofstream out("Database\\users.txt", ios_base::app);
            Printer newPrinter;
            newPrinter.printLine(out, typeOfUser + " " + login + " " + password);
        }
        cout << "Thanks for registration!\n";
        system("pause");
        system("cls");
    }

    User logIntoSystem() {
        string login, password, type;
        cout << "Hello! Let is log into system.\n";
        do {
            cout << "Enter your user-type: ";
            cin >> type;
            cout << "Enter your login: ";
            cin >> login;
            cout << "Enter your password: ";
            cin >> password;
        } while (!dataBase.foundUser(type, login, password));
        cout << "We have got such user!";
        return User(type, login, password);
    }

    void AddTest(){
        cout<<"Enter name of course: ";
        string course;
        cin>>course;
        cout<<"Enter name of lecture: ";
        string lecture;
        cin>>lecture;
        cout<<"Enter count of questions: ";
        int countOfQuestion;
        cin>>countOfQuestion;
        cout<<"Please enter questions in next format:\nQuestion\nAnswer 1\nAnswer 2\nAnswer 3\nAnswer 4\nRight answer\n"
        database.addTest("Test"+lecture, course, countOfQuestion);
    }

};
