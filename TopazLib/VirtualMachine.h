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

	Class* createClass(Class* base, const string& name);
	bool addClassVar(Class* c, const string& name);


private:
	vector<Class*>& mClasses;
	vector<Constant*>& mConstants;
	Stack mStack;
};

