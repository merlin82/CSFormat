CSFormat
========
The standard way of string formatting in C++ is sprintf or << .
The .NET Framework has its String class, which has the formatting function String.Format[^]. 
It is safer and easier to use than sprintf.

CSFormat will offer an alternative that can be used from native C++ code.


Usage
========
### Have a look at demo.cpp.
int main()
{
  cout << CSFormat("{0}|{1}|{2}", 11, "aaa", 3.14) << endl;
  return 0;
}

Compile
========
need c++ 11 support

Extension
========
