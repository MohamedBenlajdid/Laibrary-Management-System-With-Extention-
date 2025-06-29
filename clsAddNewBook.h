#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsScreen.h"


class clsAddNewBook : protected clsScreen
{
private:
	static void _PrintBookRecord(clsBook Book)
	{
		cout << "\n" << setw(37) << left << "" << "==============================\n";
		cout << "\n" << setw(37) << left << "" << "\t   Book Info \n";
		cout << "\n" << setw(37) << left << "" << "==============================\n"; 
		cout << "\n" << setw(37) << left << "" << "\t[1] Book ID : "  << Book.BookID;
		cout << "\n" << setw(37) << left << "" << "\t[2] Book Name : " << Book.BookName;
		cout << "\n" << setw(37) << left << "" << "\t[3] Book Writer : " << Book.BookWriter;
		cout << "\n" << setw(37) << left << "" << "\t[4] Book Price : " << Book.BookPrice;
		cout << "\n" << setw(37) << left << "" << "==============================\n";
	}
	static clsBook _ReadBookInfos(clsBook Book)
	{
		
		cout << "\n" << setw(37) << left << "" << "\t[2] Enter Book Name : ";
		Book.BookName = clsInputValidate::ReadString();
		cout << "\n" << setw(37) << left << "" << "\t[3] Enter Book Writer : " ;
		Book.BookWriter = clsInputValidate::ReadString();
		cout << "\n" << setw(37) << left << "" << "\t[4] Enter Book Price : ";
		Book.BookPrice = clsInputValidate::ReadShortNumber();
		return Book;
	}
public:
	static void ShowAddNewBookScreen()
	{
		_DrawHeaderScreen("  Add New Book Screen");
		cout << "\n" << setw(37) << left << "" << "Enter The Following Informations Please : ";
		clsBook Book = clsBook::GetAddNewBookObj();

		cout << "\n" << setw(37) << left << "" << "\t[1] Enter Book ID : ";
		Book.BookID = clsInputValidate::ReadString();
		while (clsBook::IsBookExist(Book.BookID))
		{
			cout << "\n" << setw(37) << left << "" << "\t[1] Enter Book ID (Not Existed) : ";
			Book.BookID = clsInputValidate::ReadString();
		}
		Book = _ReadBookInfos(Book);
		// Save Successfuly (Save Fonction in clsBook Class related to logic ) latter one.
		clsBook::enSave SaveResult;
		SaveResult = Book.Save();
		if (SaveResult == clsBook::enSave::eSavedSuccessfuly)
		{
			cout << "\n" << setw(37) << left << "" << "Book Added Successfuly :-) ";
		}
		else
		{
			cout << "\n" << setw(37) << left << "" << "Book Not Added Successfuly :-( ,ID was Exist. ";
		}
		// Extensions latter one.
	}
};

