
#pragma once
#include "oop.h"


class	clsTransferScreen
{
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
	static	clsBankClient _ReadInput(string msg)
	{
		string  id;
		clsBankClient   data = clsBankClient::Find("");
        do
        {
            cout << msg;
            cin >> id;
            data = clsBankClient::Find(id);
            if (data.Mode() != clsBankClient::enMode::EmptyMode)
                return (data);
            cout << "\nInvalaid Id ??\n";
        } while (1);
	}
	static	void	_PrintClient(clsBankClient data)
	{
        cout << "\n===========================\n";
        cout << "Full Name : " << data.Name() << endl;
        cout << "Id        : " << data.Id() << endl;
        cout << "Balance   : " << data.Balance() << endl;
        cout << "\n===========================\n";
	}
	static	int	_ReadAmountTransfer(clsBankClient data)
	{
		int Amount;
		do
		{
			cout << "Enter Transfer Amount ? ";
			cin >> Amount;
			if (Amount <= data.Balance())
				return (Amount);
			cout << "Amount Exceeds the available Balance, Enter another Amount ?\n";
		}while (1);
	}
	public:
	static void	ShowTransferScreen()
	{
        clsBankClient   dataFrom = clsBankClient::Find("");
        clsBankClient   dataTo = clsBankClient::Find("");
		int				Amount;
		string			input;
        _DrawScreenHeader("\t  Transfor Screen");
		dataFrom = _ReadInput("Please Enter Account Number to transfer from : ");
		_PrintClient(dataFrom);
		dataTo = _ReadInput("Please Enter Account Number to transfer : ");
		_PrintClient(dataTo);
		Amount = _ReadAmountTransfer(dataFrom);
		cout << "Are you sure you want to perform this peration? (y/n)";
		cin >> input;
		if (input == "y" || input == "Y")
		{
			// dataFrom.SetBalance(dataFrom.Balance() - Amount);
			// dataFrom.Save();
			// dataTo.SetBalance(dataTo.Balance() + Amount);
			// dataTo.Save();
			dataFrom.Transfer(Amount, dataTo,CurrentUser.UserName());
			cout << "Transfer done successfuly.\n";
		}
		else
			cout << "Transfer Failing.\n";
		_PrintClient(dataFrom);
		_PrintClient(dataTo);
	}
};