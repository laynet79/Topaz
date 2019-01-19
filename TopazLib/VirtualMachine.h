#pragma once
#include <vector>
using namespace std;

class Class;
class Constant;
#include "Stack.h"

class VirtualMachine
{
public:
	VirtualMachine(vector<Class*>& classes, vector<Constant*>& constants);
	~VirtualMachine();

	Class& cls(int index) { return *mClasses[index]; }
	Value& constant(int index);
	Stack& stack() { return mStack; }

private:
	vector<Class*>& mClasses;
	vector<Constant*>& mConstants;
	Stack mStack;
};

