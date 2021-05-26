#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "DataBase.h"

using namespace std;

class Course {
	vector<string> lectures;
	vector<string> tests;
	string name;
public:
	Course(string name){
		this->name = name;
	}

	void setLectures(vector<string> lectures) {
		this->lectures = lectures;
	}

	void setTests(vector<string> tests) {
		this->tests = tests;
	}
	vector<string>& getLectures() {
		return lectures;
	}
	vector<string>& getTests() {
		return tests;
	}

	string getName() {
		return name;
	}
};