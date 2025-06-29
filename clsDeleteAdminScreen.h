#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsBook.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"
#include "clsScreen.h"

class clsDeleteAdminScreen : protected clsScreen
{
private:
	static void _PrintAdminInfos(clsAdmin & Admin)
	{
        cout << "\n-------------------------------------\n";
        cout << "Admin Info:\n";
        cout << "-------------------------------------\n";
        cout << "User Name   : " << Admin.UserName << endl;
        cout << "Password    : " << Admin.Password << endl;
        cout << "Permissions : " << Admin.Permissions << endl;
        cout << "-------------------------------------\n";
	}
public:
    static void ShowDeleteAdminScreen()
    {
        system("cls");
        _DrawHeaderScreen("\tDelete Admin Screen");
        string UserName = "";
        cout << "\nEnter User Name Admin You Want To Delete : ";
        UserName = clsInputValidate::ReadString();
        while (!clsAdmin::IsAdminExist(UserName))
        {
            cout << "\nEnter User Name Admin You Want To Delete (Exist) : ";
            UserName = clsInputValidate::ReadString();
        }
        clsAdmin Admin = clsAdmin::Find(UserName);
        _PrintAdminInfos(Admin);

        char Ansr = 'n'; 
        cout << "\nYou Are Sure You Want To Delete This Admin ? : ";
        cin >> Ansr; 
        if (toupper(Ansr) == 'Y')
        {
            clsAdmin::enSaveResults SaveResult = Admin.Save();

            if (SaveResult == clsAdmin::enSaveResults::enSaveSuccessful)
            {
                cout << "\nAdmin Deleted SuccessFuly :-) .";
            }
            else
            {
                cout << "\nNot Deleted SuccessFuly ,Something Wrong :-( .";
            }

        }
    }
};

