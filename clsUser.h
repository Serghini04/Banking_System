#pragma once
#include "oop.h"
#include "clsUtil.h"
#include <unistd.h>
using namespace std;

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;
	static vector<string> _split(string s, string del)
	{
	    vector<string> res;
	    string word;
	    int pos;
	    while ((pos = s.find(del)) != std::string::npos)
	    {
	        word = s.substr(0, pos);
	        if (word != "")
	            res.push_back(word);
	        s.erase(0, pos + del.length());
	    }
	    if (s != "")
	        res.push_back(s);
	    return (res);
	}
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = ">>>")
    {
        vector<string> vUserData;
        vUserData = _split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], clsUtil::DecryptText(vUserData[4], 36), stoi(vUserData[5]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = ">>>")
    {

        string UserRecord = "";
        UserRecord += User.Name() + Seperator;
        UserRecord += User.Email() + Seperator;
        UserRecord += User.Phone() + Seperator;
        UserRecord += User.UserName() + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password(), 36) + Seperator;
        UserRecord += to_string(User.Permissions());

        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }
    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
        {
            if (U.UserName() == UserName())
            {
                U = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", 0);
    }
public:

    clsUser(enMode Mode, string Name,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(Name, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string UserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string Password()
    {
        return _Password;
    }
    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int Permissions()
    {
        return _Permissions;
    }
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName() == UserName && User.Password() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
                return enSaveResults::svFaildEmptyObject;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }
        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
                return enSaveResults::svFaildUserExists;
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
        }
        return enSaveResults::svFaildUserExists;
    }
    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
        {
            if (U.UserName() == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }
    static clsUser AddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", UserName, "", 0);
    }
    static vector <clsUser> UsersList()
    {
        return _LoadUsersDataFromFile();
    }
    enum enPermissions{eALL = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
     pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 256};
    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions() == enPermissions::eALL)
            return true;

        if ((Permission & this->Permissions()) == Permission)
        {
            return true;
        }
        else
            return false;

    }
};