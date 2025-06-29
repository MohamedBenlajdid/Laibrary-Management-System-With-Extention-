#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsScreen.h"

class clsListBooks : protected clsScreen
{
private:
	static void _PrintBookRecord(clsBook Book)
	{
		cout << "\n\t|" << setw(10) << left << Book.BookID;
		cout << "|" << setw(25) << left << Book.BookName;
		cout << "|" << setw(25) << left << Book.BookWriter;
		cout << "|" << setw(7) << left << Book.BookPrice;
		cout << "|" << setw(7) << left << Book.Available;
	}
public:
	static void ShowListBooksScreen()
	{
		_DrawHeaderScreen("  Books List Screen");

		cout << "\n\t===============================================================================\n";
		cout << "\n\t|" << setw(10) << left << "Book ID";
		cout << "|" << setw(25) << left << "Book Name";
		cout << "|" << setw(25) << left << "Book Writer";
		cout << "|" << setw(7) << left << "Price";
		cout << "|" << setw(7) << left << "Availb";
		cout << "\n\t===============================================================================\n";

		vector <clsBook> vBooks = clsBook::GetListBooks();
		for (clsBook& B : vBooks)
		{
			_PrintBookRecord(B);
		}

		cout << "\n\t===============================================================================\n";
	}
};

