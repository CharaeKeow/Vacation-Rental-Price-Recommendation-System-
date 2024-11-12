#include "VacationRental.h"
#include "Owner.h"
#include "MainMenu.h"
#include "OwnerMenu.h"
#include "PropertyMenu.h"
#include "OwnerController.h"
#include <mysql.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

//Global var
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
string icNum = "1234567890"; //current id of login-ed user (maybe will change it to PBR)
//string icNum;
//PBR == pass by reference
//end of global var

//Connect DB
class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "db_vacation_rental_price_recommendation_system", 3360, NULL, 0);
		if (conn)
		{
			//cout << "Database Connected To MySql" << conn << endl;
			cout << "Database Connected" << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}
};

int verifyUserMenu();
bool login(string &); //pass by reference
void registration();

int main() {

	//Test menu for now
	db_response::ConnectionFunction(); //Test connection
	
	//Disabled for now
	/* 
	int choice = verifyUserMenu();

	if (choice == 1) {
		login(icNum);
	} else if (choice == 2) {
		registration(); 
	} else if (choice == 3) {
		cout << "Program exited." << endl;
		exit(0);
	} else {
		verifyUserMenu(); //recursion, call the menu again until the right input is entered
	}
	*/

	int currentUser; //the userid of this user. Will be passed by ref to get the value (during login)
	
	int mainMenuChoice = 0;
	
	
	//OwnerController::addOwner(); Only invoked during registration
	MainMenu mm;
	mm.displayOptions();
	mm.selectOption(3);
	//OwnerController::displayOwner("1");
	return 0;
}

int verifyUserMenu() {
	int choice;
	cout << "Vacation Rental Price Recommendation System" << endl;
	cout << "===========================================" << endl;
	cout << "Have an account? Login. Consider register if you haven't had an account yet." << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your option: ";
	cin >> choice;

	return choice;
}

bool login(string &icNum) {
	bool success = false; //for login result

	string ic, password;
	system("cls");
	cout << "Login" << endl;
	cout << "=====" << endl << endl;

	cout << "Please enter your icNum and passwords." << endl;
	cout << "IC Number: ";
	cin >> ic;
	cout << "Password: ";
	cin >> password;

	string login = "SELECT * FROM `owner` WHERE `password` LIKE '" + password + "' AND `icNum` LIKE '" + ic + "'";
	const char* qn = login.c_str();
	qstate = mysql_query(conn, qn);

	cout << endl;
	if (!qstate) {
		res = mysql_store_result(conn);
		int i = 0;
		while ((row = mysql_fetch_row(res))) {
			success = true;
		} 
		
		if (success) {
			cout << "Successfully login" << endl;
		}
		else {
			cout << "Record not found. Make sure you enter the correct IC and password" << endl;
		}
	} else {
		cout << "Problem extracting login info from database" << endl;
	}
	return success;
}

void registration() {
	OwnerController::addOwner();
}

//Function definition for OwnerController class
bool OwnerController::addOwner() {
	system("cls");
	string name, icNum, email, password;
	int age;

	cout << "Adding user profile" << endl;
	cout << "Please enter your information:" << endl;

	cout << "Name: ";
	cin >> name;
	
	cout << "IC Number: ";
	cin >> icNum;

	cout << "Password: ";
	cin >> password;

	cout << "Email";
	cin >> email;

	cout << "Age: ";
	cin >> age;

	//db add user
	//check if ic already exist
	//if yes, reenter icNum (and password?)

	//turn int into string
	stringstream stringAge;
	string sAge;
	stringAge << age; 
	stringAge >> sAge;

	string insert_query = "INSERT INTO `db_vacation_rental_price_recommendation_system`.`owner` (`password`, `name`, `icNum`, `email`, `age`) VALUES ('" + password + "', '" + name + "', " + icNum + ", '" + email + "', '" + sAge + "');";

	const char* q = insert_query.c_str(); //c_str converts string to constant char. seems required

	qstate = mysql_query(conn, q);

	if (!qstate) {
		cout << "\nSuccessfully added into database" << endl;
	} else {
		cout << "\nQuery Execution Problem!" << mysql_errno(conn) << endl;	
	}
}

//Menus
void OwnerMenu::processOptions(int option) {
	if (option == 1) {
		cout << "User profile" << endl;

		cout << "Your profile: " << endl;

		string q = "select * from owner where icNum like '" + icNum + "'";
		const char* qn = q.c_str();
		qstate = mysql_query(conn, qn);

		if (!qstate) {
			system("cls");
			cout << "Your profile " << endl;
			cout << "============ " << endl;
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				if (atoi(row[4]) > 0) {					
					cout << "Name: " << row[1] << endl;
					cout << "IC Number: " << row[2] << endl;
					cout << "Email: " << row[3] << endl;
					cout << "Age: " << row[4] << endl;
				}
			}
		}
		else {
			cout << "Query extraction problem!" << mysql_errno(conn) << endl;
		}
		cout << endl;
		OwnerMenu::displayOptions();
	}
	else if (option == 2) {
		cout << "Update user profile" << endl;
		cout << "What do you want to update?" << endl;
		cout << "1. Name" << endl;
		cout << "2. IC Number" << endl;
		cout << "3. Email" << endl;
		cout << "4. Age" << endl;
		cout << "Choice: ";
		
		int option = 0;

		cin >> option;
		
		if (option == 1) {
			string name;
			cout << "Enter new name: ";
			cin.ignore();
			getline(cin, name);
			
			//insert SQL update name
			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `name` = '" + name + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			} else {
				cout << "\nFailed to update" << endl;
			}

			OwnerMenu::displayOptions();

		} else if (option == 2) {
			//This is primary key though 
			//Further thought needed about the need to change it or not
			string icNo;
			cout << "Enter new IC Number: ";
			cin.ignore();
			getline(cin, icNo);

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `icNum` = '" + icNo + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}

			OwnerMenu::displayOptions();

		} else if (option == 3) {
			string email;
			cout << "Enter new email address: ";
			cin.ignore();
			getline(cin, email);

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + email + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			OwnerMenu::displayOptions();

		} else if (option == 4) {
			int age = 0;
			cout << "Enter the new age: ";
			cin >> age;

			stringstream stringAge;
			string sAge;
			stringAge << age;
			stringAge >> sAge;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `age` = '" + sAge + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			OwnerMenu::displayOptions(); 
		}
	}
	else if (option == 3) {
		
		//Confirm delete
		cout << "Are you you want to delete your profile? All information";
		cout << "saved will be losed." << endl;

		//Tell possible input. TODO: loop until right input entered
		cout << "Yes(Y)/No(N): ";
		string ans;
		cin >> ans;
		if (ans == "Y" || ans == "y") {
			//base on current session (during login)
			//delete this userid (IC)
			string delete_query = "DELETE FROM `db_vacation_rental_price_recommendation_system`.`owner` WHERE `owner`.`icNum`=" + icNum;
			
			const char* qd = delete_query.c_str();
			qstate = mysql_query(conn, qd);
		}
		else if (ans != "N" || ans != "n") {
			//display OwnerMenu
			OwnerMenu::displayOptions();
		}
	} 
};

void PropertyMenu::processOptions(int option) {
	if (option == 1) {
		VacationRental vr;

		string name, address, postcode;
		int bedroom = 0, bathroom = 0, capacity = 0, nearbyAttractions = 0;
		double price = 0.0;
		bool kitchen = 0, pool = 0, aircond = 0;

		system("cls");

		//Fix the problem when using getline after using cin, which makes the stream
		//unable to use getline properly (something like that ^_^)
		cin.ignore(100, '\n');

		cout << "Enter name: ";
		getline(cin, name);
		//cin.ignore();
		
		cout << "Address: ";
		getline(cin, address);
		//cin.ignore();

		cout << "Postcode: ";
		getline(cin, postcode);
		//cin.ignore();

		cout << "No of bedroom: ";
		cin >> bedroom;
		//cin.ignore();

		cout << "No of bathroom: ";
		cin >> bathroom;
		//cin.ignore();

		cout << "Capacity: ";
		cin >> capacity;
		//cin.ignore();

		cout << "No of nearby attractions: ";
		cin >> nearbyAttractions;
		//cin.ignore();

		cout << "Has pool?";
		cin >> pool;
		//cin.ignore();

		cout << "Has airconditioning?";
		cin >> aircond;
		//cin.ignore();

		cout << "Has kitchen?";
		cin >> kitchen;
		//cin.ignore();

		cout << "Price:";
		cin >> price;
		
		cout << "Helloo World" << endl;
		cout << name << endl; 
		
		//SQL add property
		
		stringstream streamBedroom, streamBathroom, streamCapacity, streamPrice, streamHasKitchen,
			streamHasPool, streamHasAircond, streamNearbyAttractions;
		string sBedroom, sBathroom, sCapacity, sPrice, sHasKitchen, sHasPool, sHasAircond, sNearbyAttractions;
		
		streamBedroom << bedroom;
		streamBedroom >> sBedroom;
		streamBathroom << bathroom;
		streamBathroom >> sBathroom;
		streamCapacity << capacity;
		streamCapacity >> sCapacity;
		streamPrice << price;
		streamPrice >> sPrice;
		streamHasKitchen << kitchen;
		streamHasKitchen >> sHasKitchen;
		streamHasPool << pool;
		streamHasPool >> sHasPool;
		streamHasAircond << aircond;
		streamHasAircond >> sHasAircond;
		streamNearbyAttractions << nearbyAttractions;
		streamNearbyAttractions >> sNearbyAttractions;

		string insert_query = "INSERT INTO `db_vacation_rental_price_recommendation_system`.`vacationrental`(`name`, `bedroom`, `bathroom`, `capacity`, `price`, `hasKitchen`, `hasPool`, `hasAircond`, `nearbyAttractions`, `address`, `postcode`) VALUES ('"
			+ name + "', '" + sBedroom + "', '" + sBathroom + "', '" + sCapacity + "', '" + sPrice + "', '" + sHasKitchen + "', '" + sHasPool + "', '" + sHasAircond + "', '" + sNearbyAttractions + "', '" + address + "', '" + postcode + "');";

		const char* q = insert_query.c_str();

		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << endl << "Successfully added in database." << endl;
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}

		PropertyMenu::displayOptions();
		
	}
	else if (option == 2) {
		cout << "Update property" << endl;
		
		string name, address, postcode;
		int bedroom, bathroom, capacity, nearbyAttractions;
		double price;
		bool kitchen, pool, aircond;
		
		//if he has more than 1 props
		//cout << "Which property do you want to update?" << endl;
		//display all props
		//fetch that property from db

		cout << "What do you want to update?" << endl;

		cout << "1. Property name" << endl;
		cout << "2. No. of bedroom" << endl;
		cout << "3. No. of bathroom" << endl;
		cout << "4. Capacity" << endl;
		cout << "5. Price" << endl;
		cout << "6. Has kitchen" << endl;
		cout << "7. Has pool" << endl;
		cout << "8. Has aircond" << endl;
		cout << "9. No of nearby attractions" << endl;
		cout << "10. Address" << endl;
		cout << "11. Postcode" << endl;
		
		int choice;
		cout << "Update: " << endl;
		cin >> choice;	

		//Too much conditions, so let's switch
		switch (choice) { 
		case 1: {
			cout << "Enter new property name: ";
			getline(cin, name);

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + name + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();

			break;
		} {
		case 2:
			cout << "Enter new no of bedroom: ";
			cin >> bedroom;

			stringstream streamBedroom;
			string sBedroom;
			streamBedroom << bedroom;
			streamBedroom >> sBedroom;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sBedroom + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 3:
			cout << "Enter new no of bathroom: ";
			cin >> bathroom;

			stringstream streamBathroom;
			string sBathroom;
			streamBathroom << bedroom;
			streamBathroom >> sBathroom;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sBathroom + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 4:
			cout << "Enter new capacity: ";
			cin >> capacity;

			stringstream streamCapacity;
			string sCapacity;
			streamCapacity << capacity;
			streamCapacity >> sCapacity;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sCapacity + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 5: 
			cout << "Enter new price: ";
			cin >> price;

			stringstream streamPrice;
			string sPrice;
			streamPrice << price;
			streamPrice >> sPrice;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sPrice + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 6: 
			cout << "Is the kitchen available?: ";
			cin >> kitchen;

			stringstream streamKitchen;
			string sKitchen;
			streamKitchen<< kitchen;
			streamKitchen >> sKitchen;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sKitchen + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 7:
			cout << "Is the pool available?: ";
			cin >> pool;

			stringstream streamPool;
			string sPool;
			streamPool << pool;
			streamPool >> sPool;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sPool + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 8:
			cout << "Is the aircond provided?: ";
			cin >> aircond;

			stringstream streamAircond;
			string sAircond;
			streamAircond << aircond;
			streamAircond >> sAircond;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sAircond + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 9:
			cout << "Enter new no of nearby attractions: ";
			cin >> nearbyAttractions;
			
			stringstream streamNearbyAttractions;
			string sNearbyAttractions;
			streamNearbyAttractions << nearbyAttractions;
			streamNearbyAttractions >> sNearbyAttractions;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sNearbyAttractions + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();

			break;
		} {
		case 10: 
			cout << "Enter new address: ";
			cin >> address;

			stringstream streamAddress;
			string sAddress;
			streamAddress << address;
			streamAddress >> sAddress;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sAddress + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		} {
		case 11:
			cout << "Enter new postcode: ";
			cin >> postcode;

			stringstream streamPostcode;
			string sPostcode;
			streamPostcode << postcode;
			streamPostcode >> sPostcode;

			string update_query = "UPDATE `db_vacation_rental_price_recommendation_system`.`owner` SET `email` = '" + sPostcode + "' WHERE `owner`.`icNum` = '" + icNum + "'; ";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				cout << "\nSuccessfully saved in databased" << endl;
			}
			else {
				cout << "\nFailed to update" << endl;
			}
			PropertyMenu::displayOptions();
			break;
		}
		default:
			return;
		}		
	} else if (option == 3) {
		cout << "Delete property" << endl;
		cout << "These are your properties: " << endl;
		int prop = 0;
		string name[100];

		string query = "SELECT * FROM `vacationrental` WHERE `icNum` LIKE '" + icNum + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			res = mysql_store_result(conn);
			int i = 1;
			//Check if that user has more than 1 property

			while ((row = mysql_fetch_row(res))) { //display only name
				cout << i << ". " << row[1] << endl;
				name[prop] = row[1];
				i++;
				prop++;
			}					
		}

		//multi prop: ask them to select one first before sending termination command. Damn this level of English, you're a man of culture
		int choice = 0; //default to the first element in the list
		if (prop >= 1) {
			cout << "Enter the number of the property that you want to delete: ";
			cin >> choice;
			cout << name[choice-1]; //because user's option starts from 1

			cout << "Are you sure you want to delete this property? All data saved will be deleted. (Y/N)";
			string sure;
			cin >> sure;

			if (sure == "Y" || sure == "y") {

				string delete_query = "DELETE FROM `db_vacation_rental_price_recommendation_system`.`vacationrental` WHERE `vacationrental`.`name` LIKE '" + name[choice - 1] + "'";
				const char* qd = delete_query.c_str();
				qstate = mysql_query(conn, qd);

				if (!qstate) {
					cout << "Successfully delete from database." << endl;
				}
				else {
					cout << "Fail to delete!" << mysql_errno(conn) << endl;
				}
			}
			else if (sure == "N" || sure == "n") {
				//exit to main menu	
			}
			else {
				cout << "Invalid input!" << endl;
			}
		} else {
			cout << "Sorry but you have no property." << endl << endl;
		}				

		PropertyMenu::displayOptions();
	} else if (option == 4) {
		system("cls");
		cout << "View property" << endl;
		//sql display props under this userid

		string query = "SELECT * FROM `vacationrental` WHERE `icNum` LIKE '" + icNum + "'";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			res = mysql_store_result(conn);
			while ((row = mysql_fetch_row(res))) {
				cout << "Name: " << row[1] << endl;
				cout << "Address: " << row[10] << endl;
				cout << "Postcode: " << row[11] << endl;
				cout << "Bedroom: " << row[2] << endl;
				cout << "Bathroom: " << row[3] << endl;
				cout << "Capacity: " << row[4] << endl;
				cout << "Price: " << row[5] << endl;
				cout << "Has Kitchen: " << row[6] << endl;
				cout << "Has Pool: " << row[7] << endl;
				cout << "Has Aircond: " << row[8] << endl;				
				cout << "Nearby Attractions: " << row[9] << endl << endl;
			}
		}
		PropertyMenu::displayOptions();
	} else if (option == 5) {
		
		//{TODO}
		//need to do web scraping and do calculation & recommendation engine :(

	}
}