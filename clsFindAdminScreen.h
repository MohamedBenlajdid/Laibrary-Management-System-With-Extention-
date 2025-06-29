#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"
#include "clsScreen.h"

class clsFindAdminScreen : protected clsScreen
{
private:
    static void _PrintAdminInfos(clsAdmin& Admin)
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
    static void ShowFindAdminScreen()
    {
        system("cls");
        _DrawHeaderScreen("\tFind Admin Screen");
        string UserName = "";
        char Ansr = 'n';

        do
        { 
        cout << "\nEnter Admin UserName : ";
        UserName = clsInputValidate::ReadString();
        while (!clsAdmin::IsAdminExist(UserName))
        {
            cout << "\nEnter Admin UserName(Existed) : ";
            UserName = clsInputValidate::ReadString();
        }
        clsAdmin Admin = clsAdmin::Find(UserName);
        cout << "\nAdmin Infos : ";
        _PrintAdminInfos(Admin);
        cout << "\nDo You Want Find Another Admin ? : ";
        cin >> Ansr;

        } while (toupper(Ansr) == 'Y');

    }
};

