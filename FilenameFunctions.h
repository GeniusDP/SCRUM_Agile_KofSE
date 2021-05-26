#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string ext(string filePath) {//returns extention of file
    int dotPos = 1e9;
    for (int i = 0; i < filePath.size(); i++) {
        if (filePath[i] == '.') { dotPos = i; break; }
    }
    string result = "";
    for (int i = dotPos + 1; i < filePath.size(); i++) {
        result.push_back(filePath[i]);
    }
    return result;
}

//DataBase\\Course1\\file.txt -> file
string removeDirNames(string fileName) {
    string result = "";
    int pos = fileName.size() - 1;

    while (pos >= 0 && fileName[pos] != '.')pos--;
    pos--;//first character BEFORE '.' is now in fileName[pos]
    while (pos >= 0 && fileName[pos] != '\\') {
        result = fileName[pos] + result;
        pos--;
    }
    return result;
}


string changeExtention(string fileName, string newExtention) {
    string result;
    int i = 0;
    while (i < fileName.size() && fileName[i] != '.') {
        result += fileName[i];
        i++;
    }
    result += '.' + newExtention;
    return result;
}