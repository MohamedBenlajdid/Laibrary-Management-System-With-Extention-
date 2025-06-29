#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsReturnBookScreen : protected clsScreen
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
        string BookID = "";
        cout << "\nEnter Book ID : ";
        BookID = clsInputValidate::ReadString();
        while (!clsBook::IsBookExist(BookID))
        {
            cout << "\nEnter Book ID (Exist) : ";
            BookID = clsInputValidate::ReadString();
        }
        return clsBook::Find(BookID);
    }
    static void _ReturnBook(clsBook Book)
    {
        if (Book.Available)
        {
            cout << "\nThe Book Already Exist :-) . ";
        }
        else
        {
            Book.Available = 1;
            clsBook::enSave SaveResult = Book.Save();
            if (SaveResult == clsBook::enSave::eSavedSuccessfuly)
            {
                cout << "\nReturned Successfuly , Thank You For Your Contrubition :-) .";
            }
            else
            {
                cout << "\nOps ! Something Wrong , Not Returned Successfuly :-( .";
            }
        }
    }
public:
    static void ShowReturnBookScreen()
    {
        system("cls");
        _DrawHeaderScreen("\tReturn Book Screen");
        clsBook Book = _ReadBook();
        cout << "\nBook Infos(You're Borrowed) : ";
        _PrintBookInfo(Book);
        char Ansr = 'n';
        cout << "\nYour are sure you want Return this book ? : ";
        cin >> Ansr;
        if (toupper(Ansr))
        {
            _ReturnBook(Book);
        }
    }
};

