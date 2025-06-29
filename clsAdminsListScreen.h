#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"
#include "clsScreen.h"

class clsAdminsListScreen : protected clsScreen
{
private:
	static void _PrintAdminRecord(clsAdmin Admin)
	{
		cout << "\n\t|" << setw(10) << left << Admin.UserName;
		cout << "|" << setw(25) << left << Admin.Password;
		cout << "|" << setw(25) << left << Admin.Permissions;
	}
public:
	static void ShowAdminsListScreen()
	{
		_DrawHeaderScreen("  Admins List Screen");

		cout << "\n\t===============================================================================\n";
		cout << "\n\t|" << setw(10) << left << "UserName";
		cout << "|" << setw(25) << left << "Password";
		cout << "|" << setw(25) << left << "Permissions";
		cout << "\n\t===============================================================================\n";

		vector <clsAdmin> vAdmins = clsAdmin::GetAllAdmins();
		for (clsAdmin& A : vAdmins)
		{
			_PrintAdminRecord(A);
		}

		cout << "\n\t===============================================================================\n";
	}
};

