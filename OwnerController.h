#ifndef OWNERCONTROLLER_H
#define OWNERCONTROLLER_H

class OwnerController {
private:
public:
	static bool addOwner(); 
	static bool updateOwner();
	static bool deleteOwner();
	static void displayOwner(string id); //display owner based on id
};

#endif
