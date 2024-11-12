#ifndef MAINMENU_H
#define MAINMENU_H
#include "Menu.h"

class MainMenu : public Menu {
public:
	void displayOptions();
	void processOptions(int);
};

#endif;