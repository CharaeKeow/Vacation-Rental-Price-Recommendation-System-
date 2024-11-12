#include "VacationRental.h"
#include <string>
#include <iostream>
using namespace std;

//VacationRental::VacationRental() {};

//Getters

string VacationRental::getName() const{
	return name;
}

/*
int VacationRental::getId() const {
	return id;
}
*/

int VacationRental::getBedroom() const {
	return bedroom;
}

int VacationRental::getBathroom() const {
	return bathroom;
}

int VacationRental::getCapacity() const {
	return capacity;
}

double VacationRental::getPrice() const {
	return price;
}

bool VacationRental::hasKitchen() const {
	return kitchen;
}

bool VacationRental::hasPool() const {
	return pool;
}

bool VacationRental::hasAircond() const {
	return aircond;
}

int VacationRental::getNearbyAttractions() const{
	return nearbyAttractions;
}

string VacationRental::getAddress() const {
	return address;
}

string VacationRental::getPostcode() const {
	return postcode;
}

//Setters
/*
void VacationRental::setId(int id) {
	this->id = id;
}
*/

void VacationRental::setName(string name) {
	this->name = name;
}

void VacationRental::setBedroom(int bedroom) {
	this->bedroom = bedroom;
}

void VacationRental::setBathroom(int bathroom) {
	this->bathroom = bathroom;
}

void VacationRental::setCapacity(int capacity) {
	this->capacity = capacity;
}

void VacationRental::setPrice(double price) {
	this->price = price;
}

void VacationRental::setKitchen(bool kitchen) {
	this->kitchen = kitchen;
}

void VacationRental::setPool(bool pool) {
	this->pool = pool;
}

void VacationRental::setAircond(bool aircond) {
	this->aircond = aircond;
}

void VacationRental::setNearbyAttractions(int nearbyAttractions) {
	this->nearbyAttractions = nearbyAttractions;
}

void VacationRental::setAddress(string address) {
	this->address = address;
}

void VacationRental::setPostcode(string postcode) {
	this->postcode = postcode;
}