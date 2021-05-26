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
#include <set>

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
                else
                    if (currUser.getType() == "admin") {
                        cout << "0.Log out" << endl;
                        cout << "1.Add new course" << endl;
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
                            //Санин метод добавления курса

                        }
                    }
        }//while(true)
    
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
                set<string> passedByStudentTests = bd.getAllPassedByStudentTests(user.getLogin(), currCourse.getName());
                cout << "0.Go out from course" << endl;
                currCourse.setLectures(bd.getFilesFromCourseWithExtension(currCourse.getName(), "lec"));
                currCourse.setTests(bd.getFilesFromCourseWithExtension(currCourse.getName(), "test"));
                int cnt = 0;
                for (auto f : currCourse.getLectures()) {
                    cout << ++cnt << ". Read lecture : " << removeDirNames(f) << endl;
                }
                for (auto f : currCourse.getTests()) {
                    cout << ++cnt << ". Pass test : " << removeDirNames(f);
                    if (passedByStudentTests.count(changeExtention(f, "stat"))) {
                        cout << " ---> passed";
                    }
                    cout << endl;
                }
                
                if (currCourse.getTests().size() == passedByStudentTests.size())
                        cout << "YOU HAVE PASSED ALL TESTS IN THIS COURSE!" << endl;

                int typeOfMove = 0;
                cin >> typeOfMove;
                if (typeOfMove == 0) {
                    system("cls");                                                  //got out
                    return;
                }
                else {
                    //написать проверку на корректность входных данных
                    //перейти в соответствующий раздел
                    if (typeOfMove <= currCourse.getLectures().size()) {
                        readLecture(currCourse.getName(), currCourse.getLectures()[typeOfMove-1]);
                    }
                    else 
                        if (typeOfMove <= currCourse.getLectures().size() + currCourse.getTests().size()) {
                            //cout << "NEED TO PASS A TEST!";
                            system("pause");
                            cin.ignore(1);
                            passTest(user, currCourse, currCourse.getTests()[typeOfMove - 1 - currCourse.getLectures().size()]);                //to pass test
                        }
                }
            }
            else if (user.getType() == "teacher") {
                //teacher
                cout << "0.Go out from course" << endl;
                currCourse.setLectures(bd.getFilesFromCourseWithExtension(currCourse.getName(), "lec"));
                currCourse.setTests(bd.getFilesFromCourseWithExtension(currCourse.getName(), "test"));
                int cnt = 0;//номер действия
                for (auto f : currCourse.getLectures()) {
                    cout << ++cnt << ". Read my lecture : " << removeDirNames(f) << endl;
                }
                for (auto f : currCourse.getTests()) {
                    cout << ++cnt << ". Read statictics : " << removeDirNames(f) << endl;
                }
                int addlecPos, addtestPos;
                cout << (addlecPos = ++cnt) << ". Add lecture to course" << endl;
                cout << (addtestPos = ++cnt) << ". Add test to course" << endl;
                int typeOfMove = 0;
                cin >> typeOfMove;
                if (typeOfMove == 0) {                                                      //go out
                    system("cls");
                    return;
                }
                else {
                    //написать проверку на корректность входных данных
                    //перейти в соответствующий раздел
                    //to read his/her own lecture
                    if (typeOfMove <= currCourse.getLectures().size()) {
                        readLecture(currCourseName, currCourse.getLectures()[typeOfMove-1]);//reading lecture
                    }
                    else 
                        if (typeOfMove > currCourse.getLectures().size() && typeOfMove <= currCourse.getLectures().size() + currCourse.getTests().size()) {
                            system("pause");
                            readStatistics(currCourseName, currCourse.getTests()[typeOfMove - 1 - currCourse.getLectures().size()]);                     //getting statistics on test
                            //readTest(currCourseName, currCourse.getTests()[typeOfMove-1- currCourse.getLectures().size()]);
                        }else
                            if (typeOfMove == addlecPos) {
                                addLecture(currCourse);                                                     //adding lecture
                            }
                            else
                                if (typeOfMove == addtestPos) {
                                    addTest(currCourse);                                                        //adding test
                                }
                }//else (typeOfMove != 0)
            }//teacher

        }//end while

    }//end sub

    void readLecture(string currCourseName, string lecturePath) {
        system("cls");
        cout << "<<<" << "Lecture: " << removeDirNames(lecturePath) << ">>>" << endl;
        ifstream in(lecturePath);
        string str;
        while (getline(in, str)) {
            cout << str << endl;
        }
        system("pause");
    }

    void addLecture(Course& currCourse) {
        system("cls");
        cout << "Ok. Let is add new lecture to course " << currCourse.getName() << " !" << endl;
        string lectureName;
        cout << "First of all write the name of new lecture(only one word without extention of file): ";
        cin >> lectureName;
        string pathToNewLecture = "DataBase\\" + currCourse.getName() + "\\" + lectureName + ".lec";
        currCourse.getLectures().push_back(pathToNewLecture);
        cout << "Well! Write some lines of text. Last line has to be \"NULL\"(without \"): ";
        string textLine;
        string allLectureText;
        do {
            getline(cin, textLine);
            if (textLine != "NULL")
                allLectureText += textLine + "\n";
        } while (textLine != "NULL");
        DataBase().createFileAndPrintTextIntoFile(pathToNewLecture, allLectureText);
    }
    
    void addTest(Course& currCourse) {
        system("cls");
        cout << "Ok. Let is add new test to course " << currCourse.getName() << " !" << endl;
        string testName;
        cout << "First of all write the name of new lecture(only one word without extention of file): ";
        cin >> testName;
        string pathToNewTest = "DataBase\\" + currCourse.getName() + "\\" + testName + ".test";
        string pathToNewStatisticsFile = "DataBase\\" + currCourse.getName() + "\\" + testName + ".stat";
        currCourse.getTests().push_back(pathToNewTest);
        
        //filling the test file
        int numberOfQuestions;
        cout << "Write number of tests: ";
        cin >> numberOfQuestions;
        cin.ignore(1);//ignore one space or '\n' after reading numberOfQuestions
        cout << "Well! Write " << numberOfQuestions <<" blocks of text.\nOne line for question, 4 lines for variants and 1 line for answer: " << endl;
        
        string allTestInfo;
        for (int i = 0; i < numberOfQuestions; i++) {
            //read each question
            string str;
            getline(cin, str);
            allTestInfo += str + "\n";//question

            cout << "a.";//var 1
            getline(cin, str);
            allTestInfo += str + "\n";

            cout << "b.";//var 1
            getline(cin, str);
            allTestInfo += str + "\n";

            cout << "c.";//var 1
            getline(cin, str);
            allTestInfo += str + "\n";

            cout << "d.";//var 1
            getline(cin, str);
            allTestInfo += str + "\n";

            cout << "answer: ";
            getline(cin, str);
            allTestInfo += str + "\n";
        }
        
        DataBase().createFileAndPrintTextIntoFile(pathToNewTest, allTestInfo);
        DataBase().createFileAndPrintTextIntoFile(pathToNewStatisticsFile, "");
    }//end sub

    void passTest(User& user, Course currCourse, string testName) {
        system("cls");
        DataBase bd;
        int countQuestions = 0, rightAnswers = 0;
        string question;
        ifstream in(testName);
        assert(in.is_open());
        
        while (getline(in, question)) {
            cout << "*-----------------------------------------------------------------*" << endl;
            cout << question << endl;
            ++countQuestions;
            string str;
            vector<string> variants;
            for (int i = 0; i < 4; i++) {
                getline(in, str);
                cout << char(i+'a') << ") " << str << endl;
            }
            string answer, usersAnswer;
            getline(in, answer);//read answer
            cout << "Your answer: ";
            getline(cin, usersAnswer);
            if (answer == usersAnswer) {
                ++rightAnswers;
            }
            cout << "*-----------------------------------------------------------------*" << endl;
        }
        bd.appendFile(changeExtention(testName, "stat"), string(user.getLogin() + " " + to_string(rightAnswers * 100 / countQuestions) + "\n"));
        cout << "!!!Your score: " << to_string(rightAnswers) + "/" + to_string(countQuestions) << endl;
        system("pause");
        system("cls");
    }//end sub

    void readStatistics(string currCourseName, string testPath) {
        system("cls");
        cout << "<<<" << "Statistics on test: " << removeDirNames(testPath) << ">>>" << endl;
        ifstream in( changeExtention(testPath, "stat") );
        assert(in.is_open());
        string str;
        while (getline(in, str)) {
            cout << str << endl;
        }
        system("pause");
    }

};