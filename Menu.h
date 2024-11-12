#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;

class Menu {
public:
	virtual void displayOptions() = 0 ; //abstract
	virtual void processOptions(int option) = 0; //abstract
	int selectOption(int maximum);
};

#endif