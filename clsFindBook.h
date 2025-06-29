#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindBook : protected clsScreen
{
private:
	static void _PrintBookRecord(clsBook Book)
	{
		cout << "\n" << setw(37) << left << "" << "==============================\n";
		cout << "\n" << setw(37) << left << "" << "\t   Book Info \n";
		cout << "\n" << setw(37) << left << "" << "==============================\n";
		cout << "\n" << setw(37) << left << "" << "\t[1] Book ID : " << Book.BookID;
		cout << "\n" << setw(37) << left << "" << "\t[2] Book Name : " << Book.BookName;
		cout << "\n" << setw(37) << left << "" << "\t[3] Book Writer : " << Book.BookWriter;
		cout << "\n" << setw(37) << left << "" << "\t[4] Book Price : " << Book.BookPrice;
		cout << "\n" << setw(37) << left << "" << "==============================\n";
	}
public:
	static void ShowFindBookScreen()
	{
		_DrawHeaderScreen("  Find Book Screen");
		cout << "\n" << setw(37) << left << "" << "\t[1] Enter Book ID : ";
		string BookID = clsInputValidate::ReadString();
		while (!clsBook::IsBookExist(BookID))
		{
			cout << "\n" << setw(37) << left << "" << "\t[1] Enter Book ID (Existed One) : ";
			BookID = clsInputValidate::ReadString();
		}
		
		clsBook Book = clsBook::Find(BookID);
		_PrintBookRecord(Book);
	}
};

