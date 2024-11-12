#include "MainMenu.h"
#include "OwnerMenu.h"
#include "PropertyMenu.h"
#include <iostream>
using namespace std;

void MainMenu::displayOptions() {
	cout << "Vacation Rental Price Recommendation System" << endl;
	cout << "===========================================" << endl;
	cout << "\nMain Menu" << endl;
	cout << "1. Manage user profile" << endl;
	cout << "2. Manage property info" << endl;
	cout << "3. Exit" << endl;
}

void MainMenu::processOptions(int option) {
	if (option == 1) {
		OwnerMenu om;
		om.displayOptions();
		om.selectOption(4);
		system("cls");
		displayOptions(); //MainMenu's displayOptions()
	} else  if (option == 2) {
		PropertyMenu pm;

		pm.displayOptions();
		pm.selectOption(6);
		system("cls");
		displayOptions(); //MainMenu's displayOptions()
	} else if (option == 3) {
		system("cls");
		cout << "Program exited successfully. Bye." << endl;
	}
}