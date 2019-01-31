#include <iostream>
using namespace std;
#include "../TopazLib/Topaz.h"

int main()
{
	Topaz t;
	try
	{
		t.runTest();
		//double n = 4.0;
		//Value* r = t.call(nullptr, "Math", "sqrt", 1, t.value(string("2")));
		//cout << "sqrt(" << n << ")=" << t.str(r) << endl;
	}
	catch (const char* msg)
	{
		cout << "ERROR: " << msg << endl;
	}

	system("PAUSE");
	return 0;
}
