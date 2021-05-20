#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

class User {
    string login;
    string password;
    string type;
public:
    User(string type="", string login="", string password="") {
        this->login = login;
        this->type = type;
        this->password = password;
    }
    string getType() {
        return type;
    }
    string getLogin() {
        return login;
    }
    string getPassword() {
        return password;
    }
};
