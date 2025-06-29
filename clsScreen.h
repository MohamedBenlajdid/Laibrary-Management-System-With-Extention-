#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class clsScreen
{
protected:
	static void _DrawHeaderScreen(string Title, string SubTitle = "")
	{
		cout << "\n" << setw(37) << left << "" << "--------------------------------------------------------\n\n";
		cout << "\n" << setw(37) << left << "" << "\t\t" << Title << "\n";
		if (SubTitle != "")
		{
			cout  << setw(37) << left << "" << "\t\t" << SubTitle << "\n";
		}
		cout << "\n" << setw(37) << left << "" << "--------------------------------------------------------\n\n";
	}
};

