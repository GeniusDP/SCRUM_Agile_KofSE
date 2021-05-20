#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;

class DataBase{
    string path = "DataBase";
public:
    //ищет в файле user.txt прользовател€ с конкретным логином и паролем(только дл€ входа в систему) 
    bool foundUser(string type, string login, string password) {
        string userInfo;
        ifstream in("DataBase\\users.txt");
        while (getline(in, userInfo)) {
            stringstream stream(userInfo);
            string currLogin, currPassword, currType;
            stream >> currType >> currLogin >> currPassword;
            if (currType == type && currLogin == login && currPassword == password) {
                return true;
            }
        }
        return false;
    }

    vector<string> getCoursesForTeacher(string teacherLogin) {//возвращает все курсы, которые есть у ”„»“≈Ћя с логином teacherLogin
        ifstream in("Database\\" + teacherLogin + ".txt");
        //cout << in.is_open();
        string str = "";
        vector<string> result;
        while (getline(in, str)) {
            result.push_back(str);
        }
        return result;
    }

    vector<string> getAllCoursesInSystem() {//возвращает все курсы системы
        vector<string> result;
        //...
        //нужно пройтись по директории DataBase(и только!)
        // и считать все файлы .txt, кроме users.txt
        // в них построчно записаны курсы
        //(короче задача в том, чтобы пройти по файлам учителей и считать их в вектор)

        //...
        //you need to parse directory Database
        //and read all files .txt, without users.txt
        //they consist of courses(each on its line)
        //(shorter: main problem: parse all teachers` files and read all courses into vector )
        return result;
    }

    void addTest(string nameOfTest, string nameOfCourse, int countOfQuestions) {//в эту папку записывает новый тест
        ofstream out(path + "\\" + nameOfCourse + "\\" + nameOfTest + ".txt");
        if (!out.is_open())cerr << "ERRROOORRR! File if not opened!" << endl;
        Printer printer;
        for (int i = 0; i < countOfQuestions; i++)
        {
            string str;
            getline(cin, str);//question
            printer.printLine(out, str + "\n");
            getline(cin, str);//ans1
            printer.printLine(out, str + "\n");
            getline(cin, str);//ans2
            printer.printLine(out, str + "\n");
            getline(cin, str);//ans3
            printer.printLine(out, str + "\n");
            getline(cin, str);//ans4
            printer.printLine(out, str + "\n");
            getline(cin, str);//answer(truthful)
            printer.printLine(out, str + "\n");
        }
        ofstream statFile(path + "\\" + nameOfCourse + "\\" + "StatisticTest" + nameOfTest + ".txt");
    }
    void addLecture(string pathToDir);//в эту папку записывает новую лекцию
    void removeLecture(string pathToDir);
    void removeTest(string pathToDir);
    void getStatistics(string directorypath);
    void readLecture(string pathToDir);
    void readTest(string pathToDir);


};

class User {
    string login;
    string password;
    string type;
public:
    User(string type, string login, string password) {
        this->login = login;
        this->type = type;
        this->password = password;
    }
    //void addNewCourse();
    void workInCourse(string courseName);
    void goToUserCabinet();
    void goToLectures();
    void goToTests();
};





//написана практическ полностью
//за исключением функционала добавлени€ курса, который еще не пон€тно, будет ли у учител€.
void User::goToUserCabinet() {
    DataBase dataBase;
    system("cls");
    if (this->type == "teacher") {
        //teacher
        vector<string> courses = dataBase.getCoursesForTeacher(this->login);
        int movementType = 0;
        do {
            cout << "This is your own cabinet\n";
            cout << "Choose what type of activity do you want to do:\n";
            cout << "0)Log out!\n";
            int cnt = 1;
            for (auto c : courses) {
                cout << cnt++ << ")" + c + "\n";
            }
            cin >> movementType;
            switch (movementType) {
            case 0: break;//выход из системы
            default: if (movementType < courses.size() + 1 && movementType >= 1)this->workInCourse(courses[movementType - 1]);
                   else cout << "Illegal number of course!" << endl;
            }
            system("pause");
            system("cls");
        } while (movementType != 0);
        system("cls");
        cout << "Good bye!" << endl;
        system("pause");
        system("cls");
    }
    else {
        //student
        vector<string> allCourses = dataBase.getAllCoursesInSystem();
        int movementType = 0;
        do {
            cout << "This is your own cabinet\n";
            cout << "Choose what type of activity do you want to do:\n";
            cout << "0)Log out!\n";
            int cnt = 1;
            for (auto c : allCourses) {
                cout << cnt++ << ")" + c + "\n";
            }
            cin >> movementType;
            switch (movementType) {
            case 0: break;//выход из системы
            default: if (movementType < allCourses.size() + 1 && movementType >= 1)this->workInCourse(allCourses[movementType - 1]);
                   else cout << "Illegal number of course!" << endl;
            }
            //system("pause");
            system("cls");
        } while (movementType != 0);
        system("cls");
        cout << "Good bye!" << endl;
        system("pause");
        system("cls");
    }
}

// void chooseCourse
void User::workInCourse(string courseName) {
    /*
        что € тут хочу:
        как пользователь € пришел в данный курс
        если € учитель:
            хочу добавл€ть лекции, тесты, удал€ть и те и другие(это уже не так важно), уметь просматривать их.
        если € ученик:
            хочу просматривать лекции, проходить тесты

        what do I want:
        like user I have visited this course
        if I am a teacher:
            I wanna add lectures, tests, remove `em, see `em
        if I am a student
            I wanna see all lectures of this course, pass tests
    */
    system("cls");
    string pathToDir = "DataBase\\" + courseName + "\\";//путь к файлам данного курса
    if (this->type == "teacher") {
        //teacher

        int movementType = 0;
        do {
            cout << "This is course " << courseName << endl;
            cout << "==============================================================================" << endl;
            cout << "Choose what type of activity do you want to do:\n";
            cout << "0)Leave this course!\n";
            cout << "1)Add lecture.\n";
            cout << "2)Add test.\n";
            cout << "3)Remove lecture.\n";
            cout << "4)Remove test.\n";
            cout << "5)Get statistics on test.\n";
            //on second sprint
            cout << "6)Read lecture.\n";//here only needed to ask user for name of lecture and then print it onto screen
            cout << "7)Read test\n";//here only needed to ask user for name of test and then print it onto screen

            cin >> movementType;
            switch (movementType) {
                case 0: break;//выход из из курса
                /*case 1: this->addLecture(pathToDir); break;
                case 2: this->addTest(pathToDir); break;
                case 3: this->removeLecture(pathToDir); break;
                case 4: this->removeTest(pathToDir); break;
                case 5: this->getStatistics(pathToDir); break;
                case 6: this->readLecture(pathToDir); break;
                case 7: this->readTest(pathToDir); break;
                */
            }
            system("pause");
            system("cls");
        } while (movementType != 0);
        system("cls");
    }
    else {
        //student
        int movementType = 0;
        do {
            cout << "This is course " << courseName << endl;
            cout << "==============================================================================" << endl;
            cout << "Choose what type of activity do you want to do:\n";
            cout << "0)Leave this course!\n";
            cout << "1)Read lectures.\n";
            cout << "2)Pass tests.\n";

            cin >> movementType;
            switch (movementType) {
                case 0: break;//выход из из курса(go out from the course)
                //case 1: this->goToLectures(); break;
                //case 2: this->goToTests(); break;
            }
            system("pause");
            system("cls");
        } while (movementType != 0);
        system("cls");
    }
}