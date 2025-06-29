#pragma once
#include <iostream>
#include <iomanip>
#include "clsAdmin.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsAddNewAdminScreen.h"
#include "clsDeleteAdminScreen.h"
#include "clsUpdateAdminScreen.h"
#include "clsFindAdminScreen.h"
#include "clsAdminsListScreen.h"

class clsManageAdminsScreen : protected clsScreen
{
private:
	enum enManageAdminsMenueOption {
		eAddNewAdmin = 1 , eDeleteAdmin = 2 , eUpdateAdmin = 3 , eFindAdmin = 4 ,eListAdmin = 5 ,
		eAdminMenue = 6 
	};
	static short _ReadAdminManageMenueOption()
	{
		short Option = 0;
		cout << "\n" << setw(37) << left << "" << "Enter Choice Between [1-6] :";
		Option = clsInputValidate::ReadShortNumberBetween(1, 6, "\t\t\t\tEnter Choice Between [1-6] :");
		return Option;
	}
	static void _ShowAddNewAdminScreen()
	{
		/*cout << "\nAdd New Admin Will Be Here ...";*/
		clsAddNewAdminScreen::ShowAddNewAdminScreen();
	}
	static void _ShowDeleteAdminScreen()
	{
		/*cout << "\nDelete Admin Will Be Here ...";*/
		clsDeleteAdminScreen::ShowDeleteAdminScreen();
	}
	static void _ShowUpdateAdminScreen()
	{
		/*cout << "\nUpdate Admin Will Be Here ...";*/
		clsUpdateAdminScreen::ShowUpdateAdminScreen();
	}
	static void _ShowFindAdminScreen()
	{
		/*cout << "\nFind Admin Screen Will Be Here ...";*/
		clsFindAdminScreen::ShowFindAdminScreen();
	}
	static void _ShowListAdminsScreen()
	{
		/*cout << "\nList Admin Will Be Here ...";*/
		clsAdminsListScreen::ShowAdminsListScreen();
	}
	static void _ShowAdminMenueScreen()
	{
		/*cout << "\nAdmin Menue Will Be Here ....";*/
	}
	static void _GoBackToManageAdminsScreen()
	{
		cout << "\n \t\t\t Press Any Key To Go Back To Admin Manage Screen.";
		system("pause>0");
		ShowManageAdminScreen();
	}
	static void _PerformeManageAdminsOption(enManageAdminsMenueOption Option)
	{
		switch (Option)
		{
		case enManageAdminsMenueOption::eAddNewAdmin:
			system("cls");
			_ShowAddNewAdminScreen();
			_GoBackToManageAdminsScreen();
			break;
		case enManageAdminsMenueOption::eDeleteAdmin:
			system("cls");
			_ShowDeleteAdminScreen();
			_GoBackToManageAdminsScreen();
			break;
		case enManageAdminsMenueOption::eUpdateAdmin:
			system("cls");
			_ShowUpdateAdminScreen();
			_GoBackToManageAdminsScreen();
			break;
		case enManageAdminsMenueOption::eFindAdmin:
			system("cls");
			_ShowFindAdminScreen();
			_GoBackToManageAdminsScreen();
			break;
		case enManageAdminsMenueOption::eListAdmin:
			system("cls");
			_ShowListAdminsScreen();
			_GoBackToManageAdminsScreen();
			break;
		case enManageAdminsMenueOption::eAdminMenue:
			system("cls");
			_ShowAdminMenueScreen();
			break;
		}
	}

public:
	static void ShowManageAdminScreen()
	{
		system("cls");
		_DrawHeaderScreen("\tManage Admins Screen");
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		cout << "\n" << setw(37) << left << "" << "\t\tManage Admins\n";
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		cout << "\n" << setw(37) << left << "" << "\t[1] Add New Admin .";
		cout << "\n" << setw(37) << left << "" << "\t[2] Delete Admin.";
		cout << "\n" << setw(37) << left << "" << "\t[3] Update Admin .";
		cout << "\n" << setw(37) << left << "" << "\t[4] Find Admin .";
		cout << "\n" << setw(37) << left << "" << "\t[5] List Admin .";
		cout << "\n" << setw(37) << left << "" << "\t[6] Admin Menue .";
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		_PerformeManageAdminsOption((enManageAdminsMenueOption)_ReadAdminManageMenueOption());
	}
};

