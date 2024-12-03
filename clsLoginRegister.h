#pragma once
#include "oop.h"

class	clsLoginRegister : public clsScreens
{
	string	_Date;
	string	_UserName;
	string	_Password;
	int		_Permissions;
		static clsLoginRegister _convertLineToclsLogin(string line)
		{
			clsLoginRegister User;
			vector<string> arr = clsString::Split(line, ">>>");
			User._Date = arr[0];
			User._UserName = arr[1];
			User._Password = arr[2];
			User._Permissions = stoi(arr[3]);
			return (User);
		}
		static	string _convertclsLoginRegisterToLine(clsLoginRegister data)
		{
			string	res;

			res = data._Date +">>>" +data._UserName + ">>>"+ data._Password +">>>" + to_string(data._Permissions);
			return (res + "\n");
		}
	public:
		string	Date()
		{
			return (_Date);
		}
		string	UserName()
		{
			return (_UserName);
		}
		string	Password()
		{
			return (_Password);
		}
		string	Permissions()
		{
			return (to_string(_Permissions));
		}
		static	vector<clsLoginRegister> ReadFileloginRegister( void )
		{
			vector<clsLoginRegister>	res;
			clsLoginRegister			data;
			string	line;
			fstream	fd;

			fd.open("LoginRegister.txt", ios::in);
			if (fd.is_open())
			{
				while (getline(fd, line))
				{
					data = _convertLineToclsLogin(line);
					res.push_back(data);
				}
				fd.close();
			}
			return (res);
		}
		static void SaveLoginRegisterToFile(vector<clsLoginRegister> res)
		{
			fstream	fd;

			fd.open("LoginRegister.txt", ios::out);
			if (fd.is_open())
			{
				for (auto it = res.begin() ; it != res.end() ; it++)
				{
					fd << _convertclsLoginRegisterToLine(*it);
				}
				fd.close();
			}
		}
		static	void	AddUserToLoginRegister(clsUser User)
		{
			clsLoginRegister	Data;

			Data._Date = clsDate::DateToString(clsDate::GetSystemDate()) + " - " + clsDate::getCurrentTime();
			Data._UserName = User.UserName();
			Data._Password = User.Password();
			Data._Permissions = User.Permissions();
			vector<clsLoginRegister> res = ReadFileloginRegister();
			res.push_back(Data);
			SaveLoginRegisterToFile(res);
		}
		static void PrintLoginRegisterRecordLine(clsLoginRegister data)
		{
			cout << setw(8) << left << "" << "| " << setw(25) << left << data.Date();
        	cout << "| " << setw(15) << left << data.UserName();
        	cout << "| " << setw(12) << left << data.Password();
        	cout << "| " << setw(20) << left << data.Permissions();
		}
		static	void	ShowLoginRegister( void )
		{
			vector <clsLoginRegister> res = clsLoginRegister::ReadFileloginRegister();
			string Title = "\t  Login Register List Screen";
			string SubTitle ="\t    (" + to_string(res.size()) + ") Record(s).";

			_DrawScreenHeader(Title, SubTitle);
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "____________________________\n" << endl;
			cout <<  setw(8) << left << "" << "| " << left << setw(25) << "Date / Time ";
			cout << "| " << left << setw(15) << "User Name ";
			cout << "| " << left << setw(12) << "Password";
			cout << "| " << left << setw(20) << "Permissions";
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "____________________________\n" << endl;
			if (res.size() == 0)
			    cout << "\t\t\t\tNo Login Register Available In the System!";
			else
			    for (clsLoginRegister Login : res)
			    {
			        PrintLoginRegisterRecordLine(Login);
			        cout << endl;
			    }
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "____________________________\n" << endl;
		}
};


