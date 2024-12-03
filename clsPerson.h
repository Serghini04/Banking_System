#include "oop.h"
using namespace std;

class	clsPerson
{
private:
	string	_Name;
	string	_Email;
	string	_Phone;
public:
	clsPerson(string Name, string Email, string Phone)
	{
		_Name = Name;
		_Email = Email;
		_Phone = Phone;
	}
	void	SetName(string Name)
	{
		_Name = Name;
	}
	void	SetEmail(string Email)
	{
		_Email = Email;
	}
	void	SetPhone(string Phone)
	{
		_Phone = Phone;
	}
	string	Name()
	{
		return _Name;
	}
	string	Email()
	{
		return _Email;
	}
	string	Phone()
	{
		return _Phone;
	}
};