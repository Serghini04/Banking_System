#pragma once
#include "oop.h"
#include "clsMangeUser.h"
#include "clsLoginRegister.h"
using namespace std;
class clsScreen
{
protected :
    static void _DrawScreenHeader(string Title,string SubTitle ="")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
            cout << "\n\t\t\t\t\t  " << SubTitle;
        cout << "\n\t\t\t\t\t______________________________________";
        cout << "\n\t\t\t\t\tUser : " << CurrentUser.UserName();
        cout << "\n\t\t\t\t\tDate : " << clsDate::DateToString(clsDate::GetSystemDate()) << "\n\n";
    }
};
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

            if (!CurrentUser.CheckAccessPermission(Permission))
            {
                cout << "\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
                cout << "\n\t\t\t\t\t______________________________________\n\n";
                return false;
            }
            else
                return true;

    }

class clsDeleteClientScreen :protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nName   : " << Client.Name();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.Id();
        cout << "\nPassword    : " << Client.Pin();
        cout << "\nBalance     : " << Client.Balance();
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteClientScreen()
    {
        _DrawScreenHeader("\tDelete Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExit(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        cout << "\nAre you sure you want to delete this client y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            }
            else
                cout << "\nError Client Was not Deleted\n";
        }
    }

};



class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter Name: ";
        Client.SetName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPin(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetBalance(clsInputValidate::ReadFloatNumber());
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nName   : " << Client.Name();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.Id();
        cout << "\nPassword    : " << Client.Pin();
        cout << "\nBalance     : " << Client.Balance();
        cout << "\n___________________\n";

    }

public:

    static void ShowAddNewClientScreen()
    {
        _DrawScreenHeader("\t  Add New Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExit(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();
        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
        }
    }
};
class clsUpdateClientScreen :protected clsScreen

{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nName   : " << Client.Name();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.Id();
        cout << "\nPassword    : " << Client.Pin();
        cout << "\nBalance     : " << Client.Balance();
        cout << "\n___________________\n";

    }

    static void ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter Name: ";
        Client.SetName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPin(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetBalance(clsInputValidate::ReadFloatNumber());
    }
public:
    static void ShowUpdateClientScreen()
    {
        _DrawScreenHeader("\tUpdate Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExit(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        cout << "\nAre you sure you want to update this client y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            ReadClientInfo(Client1);
            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client1.Save();
            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";

                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
    }
};


class clsClientListScreen:protected clsScreen
{

private:
   static void PrintClientRecordLine(clsBankClient Client)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.Id();
        cout << "| " << setw(20) << left << Client.Name();
        cout << "| " << setw(12) << left << Client.Phone();
        cout << "| " << setw(20) << left << Client.Email();
        cout << "| " << setw(10) << left << Client.Pin();
        cout << "| " << setw(12) << left << Client.Balance();

    }
public:
   static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
            return ;
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Client List Screen";
        string SubTitle ="\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout <<  setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (clsBankClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};


class clsFindClientScreen :protected clsScreen
{

private :
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n================================";

        cout << "\nName        : " << Client.Name();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.Id();
        cout << "\nPassword    : " << Client.Pin();
        cout << "\nBalance     : " << Client.Balance();
        cout << "\n================================\n";
    }
public:
    static void ShowFindClientScreen()
    {
        _DrawScreenHeader("\tFind Client Screen");
        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExit(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        if (Client1.Mode())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }
        _PrintClient(Client1);
    }
};

class clsMainScreen:protected clsScreen
{
    private:
		enum enMainMenueOptions {
			eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
			eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
			eManageUsers = 7, enLoginRegister = 8, eExit = 9
		};

       static short _ReadMainMenueOption()
        {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 9]? ";
            short Choice = clsInputValidate::ReadShortNumberBetween(1,9,"Enter Number between 1 to 9? ");
            return Choice;
        }

       static  void _GoBackToMainMenue()
        {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Main Menue...";

            std::cin.get(); // Consume the newline character
            std::cin.get(); // Pause the program
            ShowMainMenue();
        }
		static void _ShowAllClientsScreen()
		{
			clsClientListScreen::ShowClientsList();
		}
		static void _ShowAddNewClientsScreen()
		{
            if (CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		        clsAddNewClientScreen::ShowAddNewClientScreen();
		}
       static void _ShowDeleteClientScreen()
       {
            if (CheckAccessRights(clsUser::enPermissions::pAddNewClient))
                    clsDeleteClientScreen::ShowDeleteClientScreen();
       }

       static void _ShowUpdateClientScreen()
		{
            if (CheckAccessRights(clsUser::enPermissions::pUpdateClients))
			    clsUpdateClientScreen::ShowUpdateClientScreen();
		}
		static void _ShowFindClientScreen()
		{
            if (CheckAccessRights(clsUser::enPermissions::pFindClient))
			    clsFindClientScreen::ShowFindClientScreen();
		}
        static void _ShowTransactionsMenue()
        {
            if (CheckAccessRights(clsUser::enPermissions::pTranactions))
                clsTransactionsScreen::ShowTransactionsMenue();
        }
        static void _ShowManageUsersMenue()
        {
            if (CheckAccessRights(clsUser::enPermissions::pManageUsers))
                clsManageUsersScreen::ShowManageUsersMenue();
        }
        static void _ShowLoginRegister()
        {
            if (CheckAccessRights(clsUser::enPermissions::pLoginRegister))
                clsLoginRegister::ShowLoginRegister();
        }
        static void _Logout()
        {
            CurrentUser = clsUser::Find("", "");
        }
        static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
        {
            switch (MainMenueOption)
            {
            case enMainMenueOptions::eListClients:
            {
                system("clear");

                _ShowAllClientsScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eAddNewClient:
                system("clear");
                _ShowAddNewClientsScreen();
                _GoBackToMainMenue();
                break;

            case enMainMenueOptions::eDeleteClient:
                system("clear");
                _ShowDeleteClientScreen();
                _GoBackToMainMenue();
                break;

            case enMainMenueOptions::eUpdateClient:
                system("clear");
                _ShowUpdateClientScreen();
                _GoBackToMainMenue();
                break;

            case enMainMenueOptions::eFindClient:
                system("clear");
                _ShowFindClientScreen();
                _GoBackToMainMenue();
                break;

            case enMainMenueOptions::eShowTransactionsMenue:
                system("clear");
                _ShowTransactionsMenue();
                _GoBackToMainMenue();
                break;

            case enMainMenueOptions::eManageUsers:
                system("clear");
                _ShowManageUsersMenue();
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::enLoginRegister:
                system ("clear");
                _ShowLoginRegister();
                _GoBackToMainMenue();
            case enMainMenueOptions::eExit:
                system("clear");
                _Logout();
                break;
            }

        }

	public:


       static void ShowMainMenue()
        {

            system("clear");
            _DrawScreenHeader("\t\tMain Screen");

            cout << setw(37) << left <<""<< "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Login Register.\n";
            cout << setw(37) << left << "" << "\t[9] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
        }
};
