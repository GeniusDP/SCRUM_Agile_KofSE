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
#include "FilenameFunctions.h"
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

    void goIntoUserCabinet(User currUser) {
        while(true){
            system("cls");
            cout << "<<< USER CABINET >>>" << endl;
            cout << "Hello, " << currUser.getLogin() << endl;
            cout << "What type of movement do you want to do?\n";
            if (currUser.getType() == "student") {
                cout << "0.Log out" << endl;
                DataBase bd;
                vector<string> courses = bd.getAllCoursesInSystem();
                for (int i = 0; i < courses.size(); i++) {
                    cout << i + 1 << "." << courses[i] << endl;
                }
                int typeOfMove = 0;
                cin >> typeOfMove;
                if (typeOfMove == 0) {
                    system("cls");
                    cout << "Thanks for using our site!" << endl;
                    system("pause"); system("cls");
                    return;
                }
                else {
                    //написать проверку на корректность входных данных
                    //перейти в курс
                    goToCourse(currUser, courses[typeOfMove-1]);
                }
            }
            else
                if (currUser.getType() == "teacher") {
                    cout << "0.Log out" << endl;
                    DataBase bd;
                    vector<string> courses = bd.getCoursesForTeacher(currUser.getLogin());
                    for (int i = 0; i < courses.size(); i++) {
                        cout << i + 1 << "." << courses[i] << endl;
                    }
                    int typeOfMove = 0;
                    cin >> typeOfMove;
                    if (typeOfMove == 0) {
                        system("cls");
                        cout << "Thanks for using our site!" << endl;
                        system("pause"); system("cls");
                        return;
                    }
                    else {
                        //написать проверку на корректность входных данных
                        //перейти в курс
                        goToCourse(currUser, courses[typeOfMove - 1]);
                    }
                }
        }
    
    }//end sub
    
    void goToCourse(User user, string currCourseName) {
        DataBase bd;
        Course currCourse(currCourseName);
        while (true) {
            system("cls");
            cout << "<<<This is course " << currCourseName << ">>>" << endl;
            cout << "What can you do: " << endl;
            if (user.getType() == "student") {
                //student
                cout << "0.Go out from course" << endl;
                currCourse.setLectures(bd.getFilesFromCourseWithExtension(currCourseName, "lec"));
                currCourse.setTests(bd.getFilesFromCourseWithExtension(currCourseName, "test"));
                int cnt = 0;
                for (auto f : currCourse.getLectures()) {
                    cout << ++cnt << ". Read lecture : " << removeDirNames(f) << endl;
                }
                for (auto f : currCourse.getTests()) {
                    cout << ++cnt << ". Pass test : " << removeDirNames(f) << endl;
                }
                int typeOfMove = 0;
                cin >> typeOfMove;
                if (typeOfMove == 0) {
                    system("cls");
                    return;
                }
                else {
                    //написать проверку на корректность входных данных
                    //перейти в соответствующий раздел

                }
            }
            else if (user.getType() == "teacher") {
                //teacher
                cout << "0.Go out from course" << endl;
                currCourse.setLectures(bd.getFilesFromCourseWithExtension(currCourseName, "lec"));
                currCourse.setTests(bd.getFilesFromCourseWithExtension(currCourseName, "test"));
                int cnt = 0;//номер действия
                for (auto f : currCourse.getLectures()) {
                    cout << ++cnt << ". Read my lecture : " << removeDirNames(f) << endl;
                }
                for (auto f : currCourse.getTests()) {
                    cout << ++cnt << ". Read my test : " << removeDirNames(f) << endl;
                }
                int lecPos, testPos;
                cout << (lecPos = ++cnt) << ". Add lecture to course" << endl;
                cout << (testPos = ++cnt) << ". Add test to course" << endl;
                int typeOfMove = 0;
                cin >> typeOfMove;
                if (typeOfMove == 0) {
                    system("cls");
                    return;
                }
                else {
                    //написать проверку на корректность входных данных
                    //перейти в соответствующий раздел

                }
            }

        }//end while

    }//end sub
};