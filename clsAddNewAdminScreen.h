#pragma once
#include <iostream>
#include <iomanip>
#include "clsBook.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"
#include "clsScreen.h"

class clsAddNewAdminScreen : protected clsScreen
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
    static clsAdmin _ReadAdminInfos()
    {
        string  UserName , Password;
        short Permissions;
        cout << "\nEnter Admin UserName(Not Exist) : ";
        UserName = clsInputValidate::ReadString();
        while (clsAdmin::IsAdminExist(UserName))
        {
            cout << "\nEnter Admin UserName(Not Exist) : ";
            UserName = clsInputValidate::ReadString();
        }
        cout << "\nEnter Admin Password : ";
        Password = clsInputValidate::ReadString();
        cout << "\nPermissions Part : ";
        Permissions = _ReadAdminPermission();
        return clsAdmin(UserName, Password, Permissions, clsAdmin::enMode::enAddNewMode);
    }
public:
    static void ShowAddNewAdminScreen()
    {
        system("cls");
        _DrawHeaderScreen("\tAdd New Admin Screen");
        char Ansr = 'n';
        do
        {
            clsAdmin Admin = _ReadAdminInfos();
            clsAdmin::enSaveResults SaveResult;
            SaveResult = Admin.Save();

            if (SaveResult == clsAdmin::enSaveResults::enSaveSuccessful)
            {
                cout << "\nAdmin Added Successfuly :-) .";
            }
            else
            {
                cout << "\nAdmin Not Added Successfuly ,Something Wrong :-( .";
            }

            cout << "\nDo You Want To Add Another New Admin ? : ";
            cin >> Ansr;
        } while (toupper(Ansr) == 'Y');
    }

};

