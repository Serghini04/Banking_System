#include "oop.h"
using namespace std;

class	clsBankClient : public clsPerson
{
private:
	string	_id;
	string	_pin;
	int		_balance;
	int		_Mode;
	bool	_MarkForDelete = false;
	static clsBankClient _ConvertLineObject(string line)
	{
		vector<string> data;
		data = _split(line, ">>>");
		return (clsBankClient(enMode::UpdateMode, data[1], data[2], data[0], data[4], data[3], stoi(data[5])));
	}
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
	static string	_ConvertClientObjectToLine(clsBankClient data)
	{
		string line;
		line = data.Id()+ ">>>" + data.Name() + ">>>" + data.Email() + ">>>" + data.Pin() + ">>>" + data.Phone()+  ">>>" + to_string(data.Balance()) +"\n";
		return (line);
	}
	static vector<clsBankClient> _LoadClientFromFile()
	{
		vector	<clsBankClient> vClients;
		fstream fd;
		fd.open("database/clients.txt", ios::in);
		if (fd.is_open())
		{
			string  line;
			while (getline(fd, line))
			{
				clsBankClient Client = _ConvertLineObject(line);
				vClients.push_back(Client);
			}
			fd.close();
		}
		return (vClients);
	}
	static void _SaveClientDataToFile(vector <clsBankClient> _Clients)
	{
		fstream fd;
		fd.open("database/clients.txt", ios::out);
		string line;
		if (fd.is_open())
		{
			for (clsBankClient &C : _Clients)
			{
				if (C._MarkForDelete == false)
				{
					line =  _ConvertClientObjectToLine(C);
					fd << line;
				}
			}
			fd.close();
		}
	}
	void	_Update()
	{
		vector<clsBankClient> _vClient;
		_vClient = _LoadClientFromFile();
		for (clsBankClient &C : _vClient)
		{
			if (C.Id() == Id())
			{
				C = *this;
				C.Print();
				break;
			}
		}
		_SaveClientDataToFile(_vClient);
	}
	static clsBankClient _EmptyClientObject()
	{
		return (clsBankClient(enMode::EmptyMode, "", "", "", "", "", 0));
	}
	void	_AddNew()
	{
		vector<clsBankClient> Clients = _LoadClientFromFile();
		Clients.push_back(*this);
		_SaveClientDataToFile(Clients);
	}


    string _PrepareTransferLogRecord(float Amount,clsBankClient DestinationClient,
                                     string UserName, string Seperator = ">>>")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::DateToString(clsDate::GetSystemDate())+ clsDate::getCurrentTime() + Seperator;
        TransferLogRecord += Id() + Seperator;
        TransferLogRecord += DestinationClient.Id() + Seperator;
        TransferLogRecord += to_string((int)Amount) + Seperator;
        TransferLogRecord += to_string(Balance()) + Seperator;
        TransferLogRecord += to_string(DestinationClient.Balance()) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord + "\n";
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord( Amount,  DestinationClient,  UserName);

        fstream MyFile;
        MyFile.open("database/TransfersLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
public:
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };
	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = ">>>")
    {
        stTrnsferLogRecord TrnsferLogRecord;
        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stoi(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stoi(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stoi(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];
        return TrnsferLogRecord;

    }
	enum	enMode{EmptyMode, UpdateMode, AddNewMode};
	static	vector<clsBankClient> GetClientsList()
	{
		return (_LoadClientFromFile());
	}
	string	Id()
	{
		return (_id);
	}
	string	Pin()
	{
		return (_pin);
	}
	int	Balance()
	{
		return (_balance);
	}
	int	Mode()
	{
		return (_Mode);
	}
	void	SetPin(string pin)
	{
		_pin = pin;
	}
	void	SetBalance(int balance)
	{
		_balance = balance;
	}
	void	SetMode(int mode)
	{
		_Mode =  mode;
	}
	clsBankClient(int Mode, string Name, string Email, string id, string Phone, string pin, int balance)
	 : clsPerson(Name, Email, Phone)
	{
		_Mode = Mode;
		_id = id;
		_pin = pin;
		_balance = balance;
	}
	static	clsBankClient GetAddNewClientObject(string Id)
	{
		return (clsBankClient(enMode::AddNewMode, "", "", Id, "", "", 0));
	}
	void	Print()
	{
		std::cout << "Client Card :\n";
		std::cout << "----------------------------------\n";
		std::cout << "  Account Number " << ":" << "  "<< _id << "\n";
		std::cout << "  Name           " << ":" << "  "<< Name() << "\n";
		std::cout << "  Email          " << ":" << "  "<< Email() << "\n";
		std::cout << "  Pin Code       " << ":" << "  "<< _pin << "\n";
		std::cout << "  Phone          " << ":" << "  " << Phone() << "\n";
		std::cout << "  balance        " << ":" << "  " << _balance << "\n";
		std::cout << "----------------------------------\n";
	}
	static	clsBankClient Find(string id)
	{
		vector	<clsBankClient> vClients;
		fstream fd;
		fd.open("database/clients.txt", ios::in);
		if (fd.is_open())
		{
			string  line;
			while (getline(fd, line))
			{
				clsBankClient Client = _ConvertLineObject(line);
				if (Client._id == id)
				{
					fd.close();
					return (Client);
				}
			}
			fd.close();
		}
		return (_EmptyClientObject());
	}
	static	clsBankClient Find(string id, string pin)
	{
		vector	<clsBankClient> vClients;
		fstream fd;
		fd.open("database/clients.txt", ios::in);
		if (fd.is_open())
		{
			string  line;
			while (getline(fd, line))
			{
				clsBankClient Client = _ConvertLineObject(line);
				if (Client.Id() == id && Client.Pin() == pin)
				{
					fd.close();
					return (Client);
				}
			}
			fd.close();
		}
		return (_EmptyClientObject());
	}
	static bool IsClientExit(string id)
	{
		return (clsBankClient::Find(id).Mode() == enMode::UpdateMode);
	}
	    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {
			_Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExit(_id))
                return enSaveResults::svFaildAccountNumberExists;
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
        return enSaveResults::svFaildEmptyObject;
    }
	int	Delete()
	{
		int b = 0;
		vector<clsBankClient> Clients = _LoadClientFromFile();
		for (clsBankClient &C : Clients)
		{
			if (C.Id() == Id())
			{
				C._MarkForDelete = true;
				b = 1;
				break;
			}
		}
		_SaveClientDataToFile(Clients);
		return (b);
	}
    void Deposit(double Amount)
    {
        _balance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
		if (Amount > _balance)
			return false;
		else
		{
        	_balance -= Amount;
       		 Save();
		}
		return true;
    }
    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.Balance();
        }

        return TotalBalances;
    }
    bool Transfer(float Amount, clsBankClient &DestinationClient,string UserName)
    {
        if (Amount > Balance())
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);

        return true;
    }
    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;
        fstream MyFile;
        MyFile.open("database/TransfersLog.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            stTrnsferLogRecord TransferRecord;
            while (getline(MyFile, Line))
            {
                TransferRecord = _ConvertTransferLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;
    }
};