#include "FormatString.h"
#include <string>
#include <iostream>
#include <time.h>
using namespace std;
int main()
{
	string demo = CSFormat("{0,20}|{1,-10}|{2}|{3,30:T}|", 11, "aaa", 3.14, time(NULL));
	cout << demo << endl;
	return 0;
}
