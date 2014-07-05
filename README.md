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
