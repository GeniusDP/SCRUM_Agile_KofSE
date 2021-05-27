#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "User.h"
#include <cassert>
#include <filesystem>
#include "FilenameFunctions.h"
#include <set>
using namespace std;
using namespace filesystem;




class DataBase {
	string path;
    //DataBase\t.txt
    string GetTeacherFromFileName(string filename) {
        string result = "";
        for (int i = 9; i < filename.size() - 4; i++) {
            result += filename[i];
        }
        return result;
    }

    string GetFileNameFromTeacherName(string filename) {
        cout << "HEllo!" << endl;
        return "DataBase\\" + filename + ".txt";
    }

    void AddCourseToTeachersAndMakeItsOwnDirectory(string name, vector<string> teachers, vector<int> to_add) {
        create_directory("DataBase\\" + name);
        ofstream courses("DataBase\\courses.txt", std::ios_base::app);
        courses << name << endl;
        courses.close();
        for (auto& x : to_add) {
            cout << "x = " << x << endl;
            cout << "size " << teachers.size() << endl;
            ofstream fout(GetFileNameFromTeacherName(teachers[x]), std::ios_base::app);
            fout << name << '\n';
            fout.close();
        }
        
    }

    vector<string> GetAllTeachers() {
        vector<string> teachers;
        string directory = "DataBase";
        for (const auto& x : directory_iterator(directory)) {
            if (x.is_regular_file() && x.path().string() != "DataBase\\courses.txt" && x.path().string() != "DataBase\\users.txt") {
                teachers.push_back(GetTeacherFromFileName(x.path().string()));
            }
        }
        return teachers;
    }

    bool IsAlreadyThere(vector<int> numbers, int number) {
        if (find(numbers.begin(), numbers.end(), number) == numbers.end()) return false;
        else return true;
    }

public:
	DataBase() {
		path = "DataBase\\";
	}
    bool foundUser(User user) {
        string userInfo;
        ifstream in("DataBase\\users.txt");
        while (getline(in, userInfo)) {
            stringstream stream(userInfo);
            string currLogin, currPassword, currType;
            stream >> currType >> currLogin >> currPassword;
            if (currType == user.getType() && currLogin == user.getLogin() && currPassword == user.getPassword()) {
                return true;
            }
        }
        return false;
    }

    vector<string> getAllCoursesInSystem() {//возвращает все курсы системы
        vector<string> result;
        ifstream in(path + "courses.txt");
        assert(in.is_open());
        string str;
        while (getline(in, str)) {
            result.push_back(str);
        }
        return result;
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

    void addTest(string nameOfTest, string nameOfCourse, int countOfQuestions) {//в эту папку записывает новый тест
        setlocale(LC_ALL, "ukr");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        ofstream out(path + "\\" + nameOfCourse + "\\" + nameOfTest + ".txt");
        if (!out.is_open())cerr << "ERRROOORRR! File if not opened!" << endl;
        for (int i = 0; i < countOfQuestions; i++)
        {
            string str;
            getline(cin, str);//question
            out << str + "\n";
            getline(cin, str);//ans1
            out << str + "\n";
            getline(cin, str);//ans2
            out << str + "\n";
            getline(cin, str);//ans3
            out << str + "\n";
            getline(cin, str);//ans4
            out << str + "\n";
            getline(cin, str);//answer(truthful)
            out << str + "\n";
        }
        ofstream statFile(path + "\\" + nameOfCourse + "\\" + "StatisticTest" + nameOfTest + ".txt");
    }

    void makeNewUser(User user) {
        ofstream out(path + "users.txt", ios_base::app);
        out << user.getType() << " " << user.getLogin() << " " << user.getPassword() << endl;
        if (user.getType() == "teacher") {
            ofstream out(path + user.getLogin() + ".txt");
        }
    }

    vector<string> getFilesFromCourseWithExtension(string courseName, string extention) {
        vector<string> result;
        for (auto& entry : directory_iterator(path + courseName)) {
            string file = entry.path().u8string();
            if(ext(file) == extention)
                result.push_back(entry.path().u8string());
        }
        return result;
    }

    void createFileAndPrintTextIntoFile(string filePath, string textToPut) {
        setlocale(LC_ALL, "ukr");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        ofstream out(filePath, ios_base::app);//create and open
        out << textToPut;
        out.close();
    }

    void appendFile(string pathToFile, string info) {
        setlocale(LC_ALL, "ukr");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        ofstream out(pathToFile, ios_base::app);
        assert(out.is_open());
        out << info;
        out.close();
    }

    set<string> getAllPassedByStudentTests(string userName, string currCourseName){
        set<string> result;
        vector<string> allStatisticsFilesInTheCourse = getFilesFromCourseWithExtension(currCourseName, "stat");
        for (auto filePath : allStatisticsFilesInTheCourse) {
            ifstream in(filePath);
            string str;
            while (getline(in, str)) {
                stringstream ss;
                ss << str;
                string currUserName;
                int scoreForTheTest;
                ss >> currUserName >> scoreForTheTest;
                if (currUserName == userName && scoreForTheTest == 100) {
                    result.insert(filePath);
                }
            }
        }
        return result;
    }//end sub

    void downloadFile(string path) {
        ofstream out("Downloads\\" + removeDirNames(path) + ".lec");
        ifstream in(path);
        assert(out.is_open());
        assert(in.is_open());
        string str;
        while (getline(in, str)) {
            out << str << endl;
        }
        in.close();
        out.close();
    }

    //this

    void SubmenuOfNewCourseCreation() {
        system("cls");
        cout << "Enter the name of the new course(one word): ";
        string name;
        cin >> name;
        vector<string> teachers = GetAllTeachers();
        cout << "Select the teachers who will be the owners of this course.\n";
        cout << "For example: \"1 3 6 0\". (0 to enter results and leave).\n";
        cout << "Available teachers:\n";
        int something = 1;
        for (const auto& x : teachers) {
            cout << something << ". " << teachers[something - 1] << '\n';
            something++;
        }
        vector<int> numbers;
        int NumberOfTheTeacherToAdd = -1;
        while (NumberOfTheTeacherToAdd != 0) {
            cout << "Enter the number of teacher to add to course or zero to exit: ";
            cin >> NumberOfTheTeacherToAdd;
            if (IsAlreadyThere(numbers, NumberOfTheTeacherToAdd - 1)) {
                cout << "This teacher already in the list!\n";
            }
            else if (NumberOfTheTeacherToAdd == 0 && numbers.size() >= 1) {
                cout << "You exited!\n";
            }
            else if (NumberOfTheTeacherToAdd == 0 && numbers.size() == 0) {
                cout << "You cannot just make a corse and not gave permissions for some teachers!!\n";
                NumberOfTheTeacherToAdd = -1;
            }
            else if (NumberOfTheTeacherToAdd > teachers.size()) {
                cout << "There is less number of teachers...\n";
            }
            else if (NumberOfTheTeacherToAdd < 0) {
                cout << "There is no negative teachers :)\n";
            }
            else {
                numbers.push_back(NumberOfTheTeacherToAdd - 1);
                cout << "Teacher " + teachers[NumberOfTheTeacherToAdd - 1] + " added to the course.\n";
            }
            if (numbers.size() == teachers.size()) {
                cout << "Now you're entered all the teachers available in the system!\n";
                NumberOfTheTeacherToAdd = 0;
            }
        }
        cout << "Adding course...\n";
        AddCourseToTeachersAndMakeItsOwnDirectory(name, teachers, numbers);
        cout << "Done! Course " + name + " added!\n";
    }


};