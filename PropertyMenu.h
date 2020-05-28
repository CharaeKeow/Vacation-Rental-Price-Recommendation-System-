#ifndef PROPERTYMENU_H
#define PROPERTYMENU_H
#include "Menu.h"

class PropertyMenu : public Menu {
public:
	void displayOptions();
	void processOptions(int);
};

#endif;