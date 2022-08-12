// Chapter 20, Programming Challenge 8: Employee Tree
#include <iostream>
#include <iomanip>
#include "Employee.h"
#include "BinaryTree.h"
using namespace std;

int main()
{
	int num = 0;
	string name;	//  A new variable to hold the name
	int choice = 0;	//  For the menu
	char sure;		//  For the "are you sure"
	BinaryTree<EmployeeInfo> tree;	// create a BinaryTree object

	EmployeeInfo wkr1(1021, "John Williams");   // put data into object
	tree.insertNode(wkr1);						// put object into tree
	EmployeeInfo wkr2(1057, "Bill Witherspoon");
	tree.insertNode(wkr2);
	EmployeeInfo wkr3(2487, "Jennifer Twain");
	tree.insertNode(wkr3);
	EmployeeInfo wkr4(3769, "Sophia Lancaster");
	tree.insertNode(wkr4);
	EmployeeInfo wkr5(1017, "Debbie Reece");
	tree.insertNode(wkr5);
	EmployeeInfo wkr6(1275, "George McMullen");
	tree.insertNode(wkr6);
	EmployeeInfo wkr7(1899, "Ashley Smith");
	tree.insertNode(wkr7);
	EmployeeInfo wkr8(4218, "Josh Plemmons");
	tree.insertNode(wkr8);

	do
	{
		// Display the workforce.
		cout << "\nHere is the workforce:\n\n";
		tree.displayInOrder();


		// Add a menu to make the program dynamic
		cout << "\nPlease enter a number from the following menu options: \n"
			<< "1  Enter a new employee\n"
			<< "2  View an employee\n"
			<< "3  Delete an employee\n"
			<< "4  Exit program\n"
			<< "\n\n\nEnter your choice: ";
		cin >> choice;
		
		// It probably would have been better to rewrite all of this with a switch but I just added in
		if (choice == 4)
			exit(EXIT_SUCCESS);	// exit if they picked 4 without going any further

		cout << "\nEnter the employee ID #: ";	//No matter what they picked, we'll need an employee ID
		cin >> num;
		cin.ignore();
		if (choice == 1)
		{
			cout << "\nEnter employee name: ";	// If they're entering a new one they'll need to put in the new name
			getline(cin, name);
			EmployeeInfo *newEmp = new EmployeeInfo(num, name);	//create a new object with the info entered
			tree.insertNode(*newEmp);	//  put the new object in the tree
		}



		// Search for the employee in the tree.
		EmployeeInfo* ptr = tree.searchNode(num);
		if (ptr)
		{
			cout << "Employee was found:\n" << *ptr;
		}
		else
		{
			cout << "That employee was not found.\n\n";
		}

		//  Run this if they want to delete
		if (choice == 3)
		{
			cout << "\n\nDelete this record? y/n\n";
			cin >> sure;
			if (sure == 'y' || sure == 'Y')
				tree.remove(num);
			else
				cout << "Error: Record not removed.";
		}


	} while (true);
}