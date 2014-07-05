CSFormat
========
The standard way of string formatting in C++ is sprintf or << .

The .NET Framework has its String class, which has the formatting function String.Format[^]. 

It is safer and easier to use than sprintf.

CSFormat will offer an alternative that can be used from native C++ code.


Usage
========
### Have a look at demo.cpp.

	#include "FormatString.h"
	#include <string>
	#include <iostream>
	using namespace std;
	int main()
	{
		string demo = CSFormat("{0,20}|{1,-10}|{2}|{3,30:T}|", 11, "aaa", 3.14, time(NULL));
		cout << demo << endl;
		return 0;
	}
	
Compile
========
need c++ 11 support

Extension
========
### (1) overload operator << 
	friend ostream& operator << (ostream& fout,MyType& a);

### (2)define new format class
	//a example of extension
	template <>
	class CArg<time_t> : public CArgBase
	{
	public:
		CArg(time_t arg) : _arg(arg) {}
		virtual void format(std::ostringstream &ss, const std::string& fmt)
		{
			if (fmt[0] == 'T')
			{
				_formatTime(ss, _arg);
			}
			else
			{
				ss << _arg;
			}
		}
	private:
		time_t _arg;
	};
