#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;


class User{
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
    void choosedCourse(string courseName);
    void addTest();
    void addLecture();
    void removeLecture();
    void removeTest();
    void getStatistics(string directorypath);
    void goToUserCabinet();
};



class Printer {
public:
    void printLine(ostream& out, string buffer) {
        out << buffer << endl;
    }
};

class Registrator {
public:
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
};


class {
public:
    //ищет в файле user.txt прользователя с конкретным логином и паролем(только для входа в систему) 
    bool foundUser(string type, string login, string password) {
        string userInfo;
        ifstream in("DataBase\\users.txt");
        while (getline(in, userInfo)) {
            stringstream stream(userInfo);
            string currLogin, currPassword, currType;
            stream >> currType >> currLogin >> currPassword;
            if (currType==type && currLogin == login && currPassword == password) {
                return true;
            }
        }
        return false;
    }
    
    vector<string> getCourses(string teacherLogin) {//возвращает все курсы, которые есть у УЧИТЕЛЯ с логином teacherLogin
        ifstream in("Database\\" + teacherLogin + ".txt");
        //cout << in.is_open();
        string str = "";
        vector<string> result;
        while (getline(in, str)) {
            result.push_back(str);
        }
        return result;
    }
    
    /*
        ДОПИСАТЬ! 
    */
    vector<string> getAllCourses() {//возвращает все курсы системы
        vector<string> result;
        //...
        //нужно пройтись по директории DataBase(и только!)
        // и считать все файлы .txt, кроме users.txt
        // в них построчно записаны курсы
        //(короче задача в том, чтобы пройти по файлам учителей и считать их в вектор)
        return result;
    }
    /*
        ДОПИСАТЬ!
    */

}DataBase;

class LogIner {
public:
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
        } while (!DataBase.foundUser(type, login, password));
        cout << "We have got such user!";
        return User(type, login, password);
    }
};



//*************************************************************************
//****************************<<<MAIN>>>***********************************
//*************************************************************************
int main()
{
    cout << "Hello on our system!\nDo you want to Register or Login?\n";
    string str;
    do {
        cin >> str;
    } while (!(str == "Register" || str == "Login"));
    system("cls");
    if (str == "Register") {
        Registrator aRegistrator;
        aRegistrator.makeNewUser();
    }
    else {
        LogIner aLogIner;
        User user = aLogIner.logIntoSystem();
        cout << endl; system("pause");
        user.goToUserCabinet();
    }
    return 0;
}
//*************************************************************************
//*************************************************************************


//написана практическ полностью
//за исключением функционала добавления курса, который еще не понятно, будет ли у учителя.
void User::goToUserCabinet() {
    system("cls");
    if (this->type == "teacher") {
        //teacher
        vector<string> courses = DataBase.getCourses(this->login);
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
                default: if (movementType < courses.size()+1 && movementType >= 1)this->choosedCourse(courses[movementType-1]);
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
        vector<string> allCourses = DataBase.getAllCourses();
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
                default: if (movementType < allCourses.size() + 1 && movementType >= 1)this->choosedCourse(allCourses[movementType - 1]);
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
}

// void chooseCourse
void User::choosedCourse(string courseName) {
    /*
        что я тут хочу:
        как пользователь я пришел в данный курс
        если я учитель:
            хочу добавлять лекции, тесты, удалять и те и другие(это уже не так важно), уметь просматривать их.
        если я ученик:
        хочу просматривать лекции, проходить тесты
    */
    system("cls");
    string pathToDir = "DataBase\\courseName\\";//путь к файлам данного курса
    cout << "This is course " << courseName << endl;
    cout << "==============================================================================" << endl;
    if (this->type == "teacher") {
        //teacher
        /*
        int movementType = 0;
        do {
            cout << "Choose what type of activity do you want to do:\n";
            cout << "0)Leave this course!\n";
            cout << "1)Add lecture.\n";
            cout << "2)Add test.\n";
            cout << "3)Remove lecture.\n";
            cout << "4)Remove test.\n";
            cout << "5)Get statistics on test.\n";
            int cnt = 6;

            cin >> movementType;
            switch (movementType) {
                case 0: break;//выход из из курса
                case 1: this->addLecture(); break;
                case 2: this->addTest(); break;
                case 3: this->removeLecture(); break;
                case 4: this->removeTest(); break;
                //case 5: this->getStatistics(pathDir);
            }
            system("pause");
            system("cls");
        } while (movementType != 0);
        system("cls");*/
    }
    else {
        //student

    }
}
