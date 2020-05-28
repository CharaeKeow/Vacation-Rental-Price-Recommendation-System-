#ifndef OWNER_H
#define OWNER_H
#include <string>
#include <iostream>
using namespace std;

//template <class T>
class Owner {
private:
	string userId;
	string name;
	string icNum;
	string email;	
	int age;
public:
	//Constructor
	Owner(string, string, string, string, int);
	Owner();
	//Owner(string, string, string, string, int);
	//void addOwner();
	string getUserId() const;
	string getName() const;
	string getEmail() const;
	string getIcNum() const;
	int getAge() const;
	void setUserId(string);
	void setName(string);
	void setEmail(string);
	void setIcNum(string);
	void setAge(int);
};

#endif