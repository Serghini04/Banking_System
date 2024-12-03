#include "oop.h"

//class came from classification

// create first class
class clsPerso
{
    // data members : any variable declared inside the class.
    // member methode : any function ... .
    // By default, all members of a class are private.
    // You need to use the 'public' keyword to allow access to class members from outside the class.
    public:
        string FirstName;
        string LastName;
        //this is the name of a method.
        string FullName()
        {
            return (FirstName + " " + LastName + "\n");
        }
};

//Access Specifiers:
//1/ private : Accessible Inside the Class Only.
//2/ public :  Accessible to every one.
//3/ Protected: Accessible Inside the class and all classes inherits class.

//1-Every object has its own space in memory that holds only data members.
//2-Function members are shared by all objects in memory and have only one space allocated for them.

//Properties : are Functions (set, get) allow you to Update Private Members inside

//Abstraction “displays” only the relevant attributes of objects and “hides” the unnecessary details.

class clsCalculator
{
    private:
        long	_sum;
		long	_save_changes;
		string	_token;
	public:
        //A Constructor is a special type of member function that is called automatically when an object is created.
		clsCalculator(long sum, long save_changes, string token)
        {
            _sum = sum;
            _save_changes = save_changes;
            _token = token;
        }
        ///.

        //Destructor is the last function that is going to be called before an object is destroyed.
        //Note: If an object is created in the heap, its destructor wait to detele allocation.
		~clsCalculator()
        {
            // This approach can be useful for deallocating all dynamically allocated memory
            cout << "\n Hi, I'm Destructor ...\n";
        }
		void	Clean()
		{
			_sum = 0;
			_save_changes = 0;
			_token = "Clean";
		}
		void	Add(long nb)
		{
			_save_changes = nb;
			_token  = "Adding";
			_sum += nb;
		}
		void	Sub(long nb)
		{
			_token = "Subtracting";
			_save_changes = nb;
			_sum -= nb;
		}
		void	Div(long nb)
		{
			_token = "Dividing";
			_save_changes = nb;
			_sum /= nb;
		}
		void	Mult(long nb)
		{
			_token = "Multiplaying";
			_save_changes = nb;
			_sum *= nb;
		}
		//Static (Functions / member) can be called at class level without a need to have an object.
		// exmp ==>  clsCalculator::PrintRes
		// Modify PrintRes to take an instance of clsCalculator
		static void	PrintRes(clsCalculator &calc)
		{
		    cout << "Result After ";
		    cout << calc._token << " ";
		    cout << calc._save_changes << " is : " << calc._sum << endl;
		}
};

int main()
{
    //creating first object:
	clsCalculator t(0, 0, "Clean");
	t.Sub(66);
	t.Add(566);
	t.PrintRes(t);
    return (0);
}