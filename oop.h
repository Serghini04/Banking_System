#pragma once
#ifndef OOP_H
#define OOP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsDate.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsTransactionsSreen.h"
#include "clsMainMenue.h"
#include "global.h"
#include "clsLoginRegister.h"

class clsLoginScreen :protected clsScreens
{

private :

  static  void _Login()
    {
        bool LoginFaild = false;

        string Username, Password;
        do
        {
            if (LoginFaild)
                cout << "\nInvlaid Username/Password!\n\n";

            cout << "Enter Username? ";
            cin >> Username;
            if (cin.fail())
            {
                cout << "Input Error\n";
                exit (1);
            }
            cout << "Enter Password? ";
            cin >> Password;
            if (cin.fail())
            {
                cout << "Input Error\n";
                exit (1);
            }
            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();
        } while (LoginFaild);
        clsLoginRegister::AddUserToLoginRegister(CurrentUser);
        clsMainScreen::ShowMainMenue();
    }

public:


    static void ShowLoginScreen()
    {
        system("clear");
        _DrawScreenHeader("\t  Login Screen");
        _Login();
    }

};




#endif