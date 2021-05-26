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

using namespace std;
using namespace filesystem;




class DataBase {
	string path;
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
        ofstream out(filePath);//create and open
        out << textToPut;
        out.close();
    }

    void appendFile(string pathToFile, string info) {
        ofstream out(pathToFile, ios_base::app);
        assert(out.is_open());
        out << info;
        out.close();
    }
};