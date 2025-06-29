#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsUpdateBook : protected clsScreen
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
	static clsBook _ReadBookInfos(clsBook Book)
	{

		cout << "\n" << setw(37) << left << "" << "\t[2] Enter Book Name : ";
		Book.BookName = clsInputValidate::ReadString();
		cout << "\n" << setw(37) << left << "" << "\t[3] Enter Book Writer : ";
		Book.BookWriter = clsInputValidate::ReadString();
		cout << "\n" << setw(37) << left << "" << "\t[4] Enter Book Price : ";
		Book.BookPrice = clsInputValidate::ReadShortNumber();
		return Book;
	}
public:
	static void ShowUpdateBookScreen()
	{
		_DrawHeaderScreen("  Update Book Screen");
		cout << "\n" << setw(37) << left << "" << "\t[1] Enter Book ID : ";
		string BookID = clsInputValidate::ReadString();
		while (!clsBook::IsBookExist(BookID))
		{
			cout << "\n" << setw(37) << left << "" << "\t[1] Enter Book ID (Existed One) : ";
			BookID = clsInputValidate::ReadString();
		}
		clsBook Book = clsBook::Find(BookID);
		_PrintBookRecord(Book);
		clsBook::enSave SaveResult;
		cout << "\n" << setw(37) << left << "" << "\tAre You Sure Want To Update This Book : ";
		char Ansr = 'n'; cin >> Ansr;
		if (toupper(Ansr) == 'Y')
		{
			_ReadBookInfos(Book);
			SaveResult = Book.Save();

		if (SaveResult == clsBook::enSave::eSavedSuccessfuly)
		{
			cout << "\n" << setw(37) << left << "" << "\tBook Updated Successfuly :-) ";
		}
		else
		{
			cout << "\n" << setw(37) << left << "" << "\tBook Not Updated Successfuly :-( ";
		}

		}
	}
};

