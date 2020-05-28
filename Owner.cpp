#include "Owner.h"
#include <string>
#include <iostream>
using namespace std;

Owner::Owner(string userId, string name, string email, string icNum, int age) {
	this->userId = userId;
	this->name = name;
	this->email = email;
	this->icNum = icNum;
	this->age = age;
};

Owner::Owner() {};

string Owner::getUserId() const {
	return userId;
}

string Owner::getName() const {
	return name;
}

string Owner::getEmail() const {
	return email;
}

string Owner::getIcNum() const {
	return icNum;
}

int Owner::getAge() const {
	return age;
}

void Owner::setUserId(string userId) {
	this->userId = userId;
}

void Owner::setName(string name) {
	this->name = name;
}

void Owner::setEmail(string email) {
	this->email = email;
}

void Owner::setIcNum(string icNum) {
	this->icNum = icNum;
}

void Owner::setAge(int age) {
	this->age = age;
}