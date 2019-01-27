#include <iostream>
using namespace std;
#include "../TopazLib/Topaz.h"

int main()
{
	Topaz t;
	//try
	//{
	//	double n = 4.0;
	//	Value* r = t.call(nullptr, "Math", "sqrt", 1, t.value(n));
	//	cout << "sqrt(" << n << ")=" << t.str(r) << endl;
	//}
	//catch (char* msg)
	//{
	//	cout << "ERROR: " << msg << endl;
	//}

	t.runTest();
	system("PAUSE");
	return 0;
}
