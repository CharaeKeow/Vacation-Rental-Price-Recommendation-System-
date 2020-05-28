#ifndef OWNERMENU_H
#define OWNERMENU_H
#include "Menu.h"

class OwnerMenu : public Menu {
public:
	void displayOptions();
	void processOptions(int);
};

#endif;