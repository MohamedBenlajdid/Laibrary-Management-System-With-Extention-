#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsMember
{
private:
    enum enMode ;

    string _UserName;
    string _Password;
    string _FullName;
    string _Phone;
    string _Email;
    double _AccountBalance;
    enMode _Mode;

    static clsMember _ConvertLineToRecord(string Line, string Separator = "#//#")
    {
        vector<string> Parts = clsString::Split(Line, Separator);
        if (Parts.size() < 6)
            return _GetEmptyMemberObj();

        return clsMember(
            Parts[0], Parts[1], Parts[2], Parts[3],
            Parts[4], stod(Parts[5]), enUpdateMode
        );
    }

    static string _ConvertRecordToLine(const clsMember& Member, string Separator = "#//#")
    {
        return Member._UserName + Separator + Member._Password + Separator +
            Member._FullName + Separator + Member._Phone + Separator +
            Member._Email + Separator + to_string(Member._AccountBalance);
    }

    static void _SaveToFile(const vector<clsMember>& Members)
    {
        ofstream MyFile("Members.txt");
        for (const auto& M : Members)
        {
            MyFile << _ConvertRecordToLine(M) << "\n";
        }
        MyFile.close();
    }

    static vector<clsMember> _LoadFromFile()
    {
        vector<clsMember> vMembers;
        ifstream MyFile("Members.txt");
        string Line;

        while (getline(MyFile, Line))
        {
            clsMember M = _ConvertLineToRecord(Line);
            if (!M._UserName.empty())
                vMembers.push_back(M);
        }

        MyFile.close();
        return vMembers;
    }

    bool _Add()
    {
        vector<clsMember> Members = _LoadFromFile();
        for (auto& M : Members)
            if (M._UserName == _UserName) return false;

        Members.push_back(*this);
        _SaveToFile(Members);
        return true;
    }

    bool _Update()
    {
        vector<clsMember> Members = _LoadFromFile();
        bool found = false;

        for (auto& M : Members)
        {
            if (M._UserName == _UserName)
            {
                M = *this;
                found = true;
                break;
            }
        }

        if (found) _SaveToFile(Members);
        return found;
    }

    static clsMember _GetEmptyMemberObj()
    {
        return clsMember("", "", "", "", "", 0.0, enEmptyMode);
    }

public:
    clsMember(string UserName, string Password, string FullName,
        string Phone, string Email, double Balance, enMode mode)
        : _UserName(UserName), _Password(Password), _FullName(FullName),
        _Phone(Phone), _Email(Email), _AccountBalance(Balance), _Mode(mode)
    {
    }

    enum enMode { enEmptyMode = 0, enAddNewMode = 1, enUpdateMode = 2 };

    // Getters and setters
    string get_UserName() const { return _UserName; }
    void set_UserName(string value) { _UserName = value; }

    string get_Password() const { return _Password; }
    void set_Password(string value) { _Password = value; }

    string get_FullName() const { return _FullName; }
    void set_FullName(string value) { _FullName = value; }

    string get_Phone() const { return _Phone; }
    void set_Phone(string value) { _Phone = value; }

    string get_Email() const { return _Email; }
    void set_Email(string value) { _Email = value; }

    double get_AccountBalance() const { return _AccountBalance; }
    void set_AccountBalance(double value) { _AccountBalance = value; }

    __declspec(property(get = get_UserName, put = set_UserName)) string UserName;
    __declspec(property(get = get_Password, put = set_Password)) string Password;
    __declspec(property(get = get_FullName, put = set_FullName)) string FullName;
    __declspec(property(get = get_Phone, put = set_Phone)) string Phone;
    __declspec(property(get = get_Email, put = set_Email)) string Email;
    __declspec(property(get = get_AccountBalance, put = set_AccountBalance)) double AccountBalance;

    bool IsEmptyMemberObj() const { return _Mode == enEmptyMode; }

    enum enSaveResults { enSaveSuccess, enSaveFail_Empty, enSaveFail_Exist };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enEmptyMode:
            return enSaveFail_Empty;
        case enAddNewMode:
            if (_Add()) return enSaveSuccess;
            return enSaveFail_Exist;
        case enUpdateMode:
            if (_Update()) return enSaveSuccess;
            return enSaveFail_Empty;
        default:
            return enSaveFail_Empty;
        }
    }

    static clsMember Find(string UserName)
    {
        vector<clsMember> Members = _LoadFromFile();
        for (auto& M : Members)
        {
            if (M.UserName == UserName)
                return M;
        }
        return _GetEmptyMemberObj();
    }

    static clsMember Find(string UserName, string Password)
    {
        vector<clsMember> Members = _LoadFromFile();
        for (auto& M : Members)
        {
            if (M.UserName == UserName && M.Password == Password)
                return M;
        }
        return _GetEmptyMemberObj();
    }

    static bool IsMemberExist(string UserName)
    {
        return !Find(UserName).IsEmptyMemberObj();
    }

    static bool IsMemberExist(string UserName, string Password)
    {
        clsMember Member = Find(UserName, Password);
        return !Member.IsEmptyMemberObj();
    }

    static vector<clsMember> GetAllMembers()
    {
        return _LoadFromFile();
    }

    static clsMember GetAddNewMember(string UserName)
    {
        return clsMember(UserName, "", "", "", "", 0.0, enAddNewMode);
    }
};

