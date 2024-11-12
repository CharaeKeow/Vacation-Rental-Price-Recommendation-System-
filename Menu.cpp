#include "Menu.h"
#include <iostream>
using namespace std;

int Menu::selectOption(int maximum) {
	int option;

	do {
		option = 0; //reset choice on every iteration

		while (option < 1 || option > maximum) {
			cout << "Choose one: ";
			cin >> option;

			if (option < 1 || option > maximum) {
				cout << "\nInvalid option! Please choose a value between 1 and " << maximum << endl;
			}
		}
		processOptions(option);
	} while (option != maximum);
	return option;
}