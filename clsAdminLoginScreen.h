#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsAddNewBook.h"
#include "clsDeleteBook.h"
#include "clsUpdateBook.h"
#include "clsFindBook.h"
#include "clsListBooks.h"
#include "clsAdmin.h"
#include "clsManageAdminsScreen.h"
#include "Global.h"
using namespace std;

class clsAdminLoginScreen : clsScreen
{
private:
	enum enAdminMenueOptions {
		eAddNewBook = 1 ,eDeleteBook = 2 , eUpdateBook = 3 , eFindBook = 4 , 
		eListBooks = 5 ,eManageAdmins = 6 ,eMainMenue = 7
	};
	static short _ReadAdminMenueOption()
	{
		short Choice = 0;
		cout << "\n" << setw(37) << left << "" << "\tPlease Enter a Choice between[1-7] : ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Please Enter a Choice between[1 - 7] : ");
		return Choice;

	}
	static void _ShowAddNewBookScreen()
	{
		/*cout << "\nAdd New Book Will Be Here.";*/
		clsAddNewBook::ShowAddNewBookScreen();
	}
	static void _ShowDeleteBookScreen()
	{
		/*cout << "\nDelete Book Will Be Here.";*/
		clsDeleteBook::ShowDeleteBookScreen();
	}
	static void _ShowUpdateBookScreen()
	{
		/*cout << "\nUpdate Book Will Be Here.";*/
		clsUpdateBook::ShowUpdateBookScreen();
	}
	static void _ShowFindBookScreen()
	{
		/*cout << "\nFind Book Will Be Here .";*/
		clsFindBook::ShowFindBookScreen();
	}
	static void _ShowListBooksScreen()
	{
		/*cout << "\nList Books Will Be Here ...";*/
		clsListBooks::ShowListBooksScreen();
	}
	static void _ShowManageAdminsScreen()
	{
		/*cout << "\nManage Admin Will Be Here ...";*/
		clsManageAdminsScreen::ShowManageAdminScreen();
	}
	static void _ShowMainMenueScreen()
	{
		cout << "\nMain Menue Screen Will Be Here .";
	}
	static void _GoBackToAdminMenue()
	{
		cout << "\nPress Any Key To Go Back To Admin Menue.";
		system("pause>0");
		ShowAdminLoginScreen();
	}
	static void _PerformeAdminMenueChoice(enAdminMenueOptions Option)
	{
		switch (Option)
		{
		case enAdminMenueOptions::eAddNewBook:
			system("cls");
			_ShowAddNewBookScreen();
			_GoBackToAdminMenue();
			break;
		case enAdminMenueOptions::eDeleteBook:
			system("cls");
			_ShowDeleteBookScreen();
			_GoBackToAdminMenue();
			break;
		case enAdminMenueOptions::eUpdateBook:
			system("cls");
			_ShowUpdateBookScreen();
			_GoBackToAdminMenue();
			break;
		case enAdminMenueOptions::eFindBook:
			system("cls");
			_ShowFindBookScreen();
			_GoBackToAdminMenue();
			break;
		case enAdminMenueOptions::eListBooks:
			system("cls");
			_ShowListBooksScreen();
			_GoBackToAdminMenue();
			break;
		case enAdminMenueOptions::eManageAdmins:
			system("cls");
			_ShowManageAdminsScreen();
			_GoBackToAdminMenue();
			break;
		case enAdminMenueOptions::eMainMenue:
			system("cls");
			_AdminLogout();
			_ShowMainMenueScreen();
			break;
		}
	}
	static void _AdminLogin()
	{
		if (!CurrentAdmin.IsEmptyAdminObj())
			return; // already logged in

		system("cls");
		_DrawHeaderScreen("\tAdmin Login Screen");
		string UserName, Password;
		cout << "\n" << setw(37) << left << "" << "Enter User Name Please : ";
		UserName = clsInputValidate::ReadString();
		cout << "\n" << setw(37) << left << "" << "Enter Password Please : ";
		Password = clsInputValidate::ReadString();
		while (!clsAdmin::IsAdminExist(UserName, Password))
		{
			cout << "\n" << setw(37) << left << "" << "UserName/Password is Wrong , Try Again : ";
			cout << "\n" << setw(37) << left << "" << "Enter User Name Please : ";
			UserName = clsInputValidate::ReadString();
			cout << "\n" << setw(37) << left << "" << "Enter Password Please : ";
			Password = clsInputValidate::ReadString();
		}
		CurrentAdmin = clsAdmin::Find(UserName, Password);
	}
	static void _AdminLogout()
	{
		cout << "\n\t\t\t\t Logout :-) . \n";
		CurrentAdmin = clsAdmin("", "", 0, clsAdmin::enMode::enEmptyMode);
	}

public:
	static void ShowAdminLoginScreen()
	{
		_AdminLogin();
		system("cls");
		_DrawHeaderScreen("\tAdmin Screen");
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		cout << "\n" << setw(37) << left << "" << "\t\tAdmin Menue\n";
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		cout << "\n" << setw(37) << left << "" << "\t[1] Add New Book .";
		cout << "\n" << setw(37) << left << "" << "\t[2] Delete Book.";
		cout << "\n" << setw(37) << left << "" << "\t[3] Update Book .";
		cout << "\n" << setw(37) << left << "" << "\t[4] Find Book .";
		cout << "\n" << setw(37) << left << "" << "\t[5] List Books .";
		cout << "\n" << setw(37) << left << "" << "\t[6] Manage Admins .";
		cout << "\n" << setw(37) << left << "" << "\t[7] Logout .";
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		_PerformeAdminMenueChoice((enAdminMenueOptions)_ReadAdminMenueOption());
	}
};

