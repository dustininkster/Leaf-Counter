/////////////////////////////
// EmployeeInfo class
/////////////////////////////
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <string>
#include "BinaryTree.h"
using namespace std;

// Forware declaration of the Employee class.
class EmployeeInfo;

// Function Prototypes for Overloaded Stream Operators.
// Needed for some compilers.
ostream &operator << (ostream &, EmployeeInfo &);

class EmployeeInfo
{

private:
		int empID;
		string name;
	
public:
	friend class BinaryTree<EmployeeInfo>;

	EmployeeInfo(int id = 0, string n = "None" ) //This had an error resulting from the mismatch of a const char pointer and string. I changed it to match the main function
	{
		empID = id;
		name = n;
	}

	void setID(int n)
	{
		empID = n;
	}

	void setName(char *str)
	{
		name = str;
	}

	void setName(string str)
	{
		name = str;
	}

	int getID()
	{
		return this->empID;
	}

	bool operator==(int value)
	{
		return this->getID() == value;
	}

	string getName()
	{
		return name;
	}

	bool operator==(const EmployeeInfo& emp)
	{
		return this->empID == emp.empID;
	}

	bool operator< (const EmployeeInfo& emp)
	{
		return this->empID < emp.empID;
	}

	bool operator> (const EmployeeInfo& emp)
	{
		return this->empID > emp.empID;
	}

	friend ostream &operator<<(ostream &strm, EmployeeInfo &obj)
	{
		strm << "ID Number: " << obj.empID << "\tName: " << obj.name << endl;
		return strm;
	}

};

#endif