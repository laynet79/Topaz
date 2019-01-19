#pragma once
#include <string>
#include <vector>
using namespace std;
#include "Stack.h"
class Class;

//-------------------------------------------------------
// This class represents the implementation of Topaz and 
// is used to hide the implementation from the user of
// the Topaz library.
//-------------------------------------------------------
class TopazImp
{
public:
	TopazImp();
	~TopazImp();
	void run();
	bool compile(const string& input);

private:
	vector<Class*> mClasses;
	Stack mStack;
};

