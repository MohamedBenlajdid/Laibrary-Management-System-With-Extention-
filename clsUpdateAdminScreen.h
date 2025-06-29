#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"
#include "clsScreen.h"

class clsUpdateAdminScreen : protected clsScreen
{
private:
    static short _ReadAdminPermission()
    {
        short Permissions = 0;
        char Answer;

        cout << "Do you want to give full access? (y/n): ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
            return -1; // All permissions granted (all bits = 1)

        cout << "Do you want to give access to:\n";

        cout << "1. Admins Management? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y') Permissions |= clsAdmin::enAdminsManage;

        cout << "2. Add Book? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y') Permissions |= clsAdmin::enAddBook;

        cout << "3. Delete Book? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y') Permissions |= clsAdmin::enDeleteBook;

        cout << "4. Find Book? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y') Permissions |= clsAdmin::enFindBook;

        cout << "5. List Books? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y') Permissions |= clsAdmin::enListBook;

        return Permissions;
    }
    static clsAdmin _ReadAdminInfos(string UserName)
    {
        string  Password;
        short Permissions;
        cout << "\nEnter Admin Password : ";
        Password = clsInputValidate::ReadString();
        cout << "\nPermissions Part : ";
        Permissions = _ReadAdminPermission();
        return clsAdmin(UserName, Password, Permissions, clsAdmin::enMode::enUpdateMode);
    }
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
    static void ShowUpdateAdminScreen()
    {
        system("cls");
        _DrawHeaderScreen("\tUpdate Admin Screen");
        string UserName = "";
        cout << "\nEnter Admin UserName : ";
        UserName = clsInputValidate::ReadString();
        while (!clsAdmin::IsAdminExist(UserName))
        {
            cout << "\nPlease Enter an Exist Admin UserName : ";
            UserName = clsInputValidate::ReadString();
        }
        clsAdmin Admin = clsAdmin::Find(UserName);
        cout << "\nAdmin Infos : ";
        _PrintAdminInfos(Admin);
        char Ansr = 'n'; 
        cout << "\nAre You Sure You Want To Update This Admin ? : ";
        cin >> Ansr;
        if (toupper(Ansr) == 'Y')
        {
            Admin = _ReadAdminInfos(UserName);
            clsAdmin::enSaveResults SaveResult = Admin.Save();
            if (SaveResult == clsAdmin::enSaveResults::enSaveSuccessful)
            {
                cout << "\nUpdate Successfuly :-) . ";
            }
            else
            {
                cout << "\Something Wrong ! , Update not done successfuly :-( ";
            }

        }


    }
};

