#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsBorrowBookScreen : protected clsScreen
{
private:
    static void _PrintBookInfo(clsBook Book)
	{
        cout << "\n-----------------------------------------\n";
        cout << "\t Book Info:\n";
        cout << "-----------------------------------------\n";
        cout << "Book ID     : " << Book.BookID << "\n";
        cout << "Title       : " << Book.BookName << "\n";
        cout << "Author      : " << Book.BookWriter << "\n";
        cout << "Price       : " << Book.BookPrice << " MAD\n";
        cout << "Available   : " << (Book.Available ? "Yes" : "No") << "\n";
        cout << "-----------------------------------------\n";
	}
    static clsBook _ReadBook()
    {
        string BookID = "" ;
        cout << "\nEnter Book ID : ";
        BookID = clsInputValidate::ReadString();
        while (!clsBook::IsBookExist(BookID))
        {
            cout << "\nEnter Book ID (Exist) : ";
            BookID = clsInputValidate::ReadString();
        }
        return clsBook::Find(BookID);
    }
    static void _BorrowBook(clsBook Book)
    {
        if (!Book.Available)
        {
            cout << "\nSorry The Book Already Borrowed :-( . ";
        }
        else
        {
            Book.Available = 0;
            clsBook::enSave SaveResult = Book.Save();
            if (SaveResult == clsBook::enSave::eSavedSuccessfuly)
            {
                cout << "\nYou're Borrowed The Book Successfuly :-) .";
            }
            else
            {
                cout << "\nSomething Wrong , Not Borrowed . :-(.";
            }
        }
    }
public:
    static void ShowBorrowBookScreen()
    {
        system("cls");
        _DrawHeaderScreen("\tBorrow Book Screen");
        clsBook Book = _ReadBook();
        cout << "\nBook Infos : ";
        _PrintBookInfo(Book);
        char Ansr = 'n';
        cout << "\nYour are sure you want Borrow this book ? : ";
        cin >> Ansr;
        if(toupper(Ansr))
        { 
          _BorrowBook(Book);
        }
    }
};

