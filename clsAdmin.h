#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsAdmin
{
private:
    enum enMode;

    string _UserName;
    string _Password;
    int _Permissions;
    enMode _Mode;

    static clsAdmin _ConvertLineToRecord(string Line ,string Separator = "#//#") {
        vector<string> Parts = clsString::Split(Line,Separator);
        if (Parts.size() < 3) return _GetEmptyAdminObj();

        return clsAdmin(Parts[0], Parts[1], stoi(Parts[2]), enUpdateMode);
    }

    static string _ConvertRecordToLine(const clsAdmin& Admin, const string& Separator = "#//#") {
        return Admin._UserName + Separator + Admin._Password + Separator + to_string(Admin._Permissions);
    }

    static void _SaveToFile(const vector<clsAdmin>& Admins) {
        ofstream MyFile("Admins.txt");
        for (const auto& Admin : Admins) {
            MyFile << _ConvertRecordToLine(Admin) << "\n";
        }
        MyFile.close();
    }

    static vector<clsAdmin> _LoadFromFile() {
        vector<clsAdmin> vAdmins;
        ifstream MyFile("Admins.txt");

        string Line;
        while (getline(MyFile, Line)) {
            clsAdmin A = _ConvertLineToRecord(Line);
            if (!A._UserName.empty()) {
                vAdmins.push_back(A);
            }
        }
        MyFile.close();
        return vAdmins;
    }

    bool _Add() {
        vector<clsAdmin> Admins = _LoadFromFile();

        for (const auto& A : Admins) {
            if (A._UserName == _UserName) return false;
        }

        Admins.push_back(*this);
        _SaveToFile(Admins);
        return true;
    }

    bool _Update() {
        vector<clsAdmin> Admins = _LoadFromFile();
        bool found = false;

        for (auto& A : Admins) {
            if (A._UserName == _UserName) {
                A = *this;
                found = true;
                break;
            }
        }

        if (found) _SaveToFile(Admins);
        return found;
    }

    static clsAdmin _GetEmptyAdminObj()
    {
        return clsAdmin("", "", 0, enMode::enEmptyMode);
    }

public:
    clsAdmin(string UserName, string Password, int Permissions, enMode mode) {
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
        _Mode = mode;
    }

    enum enMode {
        enEmptyMode = 1,
        enAddNewMode = 2,
        enUpdateMode = 3
    };

    enum enPermissions {
        enAdminsManage = 1,
        enAddBook = 2,
        enDeleteBook = 4,
        enFindBook = 8,
        enListBook = 16
    };

    enum enSaveResults {
        enSaveSuccessful = 1,
        enSaveFailed_EmptyObject = 2,
        enSaveFailed_ObjectExists = 4
    };

     bool IsEmptyAdminObj()
    {
        return _Mode == enMode::enEmptyMode;
    }

     //  Required getter/setter methods
     string get_UserName() const { return _UserName; }
     void set_UserName(string value) { _UserName = value; }

     string get_Password() const { return _Password; }
     void set_Password(string value) { _Password = value; }

     int get_Permissions() const { return _Permissions; }
     void set_Permissions(int value) { _Permissions = value; }

     //  Property declarations
     __declspec(property(get = get_UserName, put = set_UserName)) string UserName;
     __declspec(property(get = get_Password, put = set_Password)) string Password;
     __declspec(property(get = get_Permissions, put = set_Permissions)) int Permissions;

    bool CheckPermission(enPermissions permission)  {
        return (_Permissions & permission) != 0;
    }

    enSaveResults Save() {
        switch (_Mode) {
        case enEmptyMode:
            return enSaveFailed_EmptyObject;

        case enAddNewMode:
            if (_Add()) return enSaveSuccessful;
            return enSaveFailed_ObjectExists;

        case enUpdateMode:
            if (_Update()) return enSaveSuccessful;
            return enSaveFailed_EmptyObject;

        default:
            return enSaveFailed_EmptyObject;
        }
    }

    static clsAdmin Find(string UserName) {
        vector<clsAdmin> Admins = _LoadFromFile();
        for (auto& A : Admins) {
            if (A.UserName == UserName)
                return A;
        }
        return _GetEmptyAdminObj();
    }
    static clsAdmin Find(string UserName,string Password) {
        vector<clsAdmin> Admins = _LoadFromFile();
        for (auto& A : Admins) {
            if (A.UserName == UserName && A.Password == Password)
                return A;
        }
        return _GetEmptyAdminObj();
    }

    static bool IsAdminExist(string UserName,string Password)
    {
        clsAdmin Admin = clsAdmin::Find(UserName,Password);
        return (!Admin.IsEmptyAdminObj());
    }
    static bool IsAdminExist(string UserName)
    {
        clsAdmin Admin = clsAdmin::Find(UserName);
        return (!Admin.IsEmptyAdminObj());
    }

    static vector<clsAdmin> GetAllAdmins() {
        return _LoadFromFile();
    }

    static clsAdmin GetAddNewAdmin(string UserName)
    {
        return clsAdmin(UserName, "", 0, enMode::enAddNewMode);
    }
};

