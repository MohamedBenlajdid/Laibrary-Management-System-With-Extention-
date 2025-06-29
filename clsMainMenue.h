#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsAdminLoginScreen.h"
#include "clsMemberLoginScreen.h"
#include "clsScreen.h"

using namespace std;

class clsMainMenue :protected clsScreen
{
private:
	enum enMainMenueOptions {
		eAdminLogin = 1, eMemberLogin = 2, eExit = 3
	};
	static short _ReadMainMenueOption()
	{
		short Choice = 0;
		cout << "\n" << setw(37) << left << "" << "\tPlease Enter a Choice between[1-3] : ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 3, "Please Enter a Choice between[1 - 3] : ");
		return Choice;
	}
	static void _ShowAdminLoginScreen()
	{
		/*cout << "\nAdmin Login Will Be Here .";*/
		clsAdminLoginScreen::ShowAdminLoginScreen();
	}
	static void _ShowMemberLoginScreen()
	{
		/*cout << "\nMember Login Will Be Here.";*/
		clsMemberLoginScreen::ShowMemberLoginScreen();
	}
	static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will Be Here .";
	}
	static void _GoBackToMainMenue()
	{
		cout << "\n" << setw(37) << left << "" << "\tPress Any Key To Comeback To Main Menue.\n";
		system("pause>0");
		ShowMainMenueScreen();
	}
	static void _PerformeMainMenueChoice(enMainMenueOptions Option)
	{
		switch (Option)
		{
		case enMainMenueOptions::eAdminLogin:
			system("cls");
			_ShowAdminLoginScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eMemberLogin:
			system("cls");
			_ShowMemberLoginScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eExit:
			system("cls");
			_ShowEndScreen();
			_GoBackToMainMenue();
			break;
		}
	}

public:


	static void ShowMainMenueScreen()
	{
		system("cls");
		_DrawHeaderScreen("\tMain Menue Screen");
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		cout << "\n" << setw(37) << left << "" << "\t\t   Main Menue\n";
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		cout << "\n" << setw(37) << left << "" << "\t[1] Admin Login.";
		cout << "\n" << setw(37) << left << "" << "\t[2] Member Login.";
		cout << "\n" << setw(37) << left << "" << "\t[3] Exit .";
		cout << "\n" << setw(37) << left << "" << "==========================================\n";
		_PerformeMainMenueChoice((enMainMenueOptions)_ReadMainMenueOption());

	}
};

