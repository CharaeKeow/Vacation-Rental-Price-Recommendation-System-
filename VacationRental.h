#ifndef VACATIONRENTAL_H
#define VACATIONRENTAL_H
#include <string>
#include <iostream>
using namespace std;

class VacationRental {
private:
	//int id;
	string name;
	int bedroom;
	int bathroom;
	int capacity;
	double price;
	bool kitchen;
	bool pool;
	bool aircond;
	int nearbyAttractions;
	string address;
	string postcode;
public:
	//Getters
	//int getId() const;
	string getName() const;
	int getBedroom() const;
	int getBathroom() const;
	int getCapacity() const;
	double getPrice() const;
	bool hasKitchen() const;
	bool hasPool() const;
	bool hasAircond() const;
	int getNearbyAttractions() const;
	string getAddress() const;
	string getPostcode() const;

	//Setters
	//void setId(int);
	void setName(string);
	void setBedroom(int);
	void setBathroom(int);
	void setCapacity(int);
	void setPrice(double);
	void setKitchen(bool);
	void setPool(bool);
	void setAircond(bool);
	void setNearbyAttractions(int);
	void setAddress(string);
	void setPostcode(string);
};

#endif