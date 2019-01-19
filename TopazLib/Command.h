#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Symbol.h"

//-------------------------------------------------------
// This class represents a virtual machine instruction
// (base class)
//-------------------------------------------------------
class Command
{
public:
	Command(int line, Symbol* a0 = nullptr, Symbol* a1 = nullptr, Symbol* a2 = nullptr) : mLine(line)
	{ mArg[0] = a0; mArg[1] = a1; mArg[2] = a2; }
	virtual string name() const = 0;
	Symbol* arg(int arg) const { return mArg[arg]; }
	virtual bool run(VirtualMachine& vm, int& pc) = 0;
protected:
	Value& value(VirtualMachine& vm, int arg, Value::Type type=Value::ANY);
	Symbol* mArg[3];
	int mLine;
	void error(const string& msg) { throw string("line ") + to_string(mLine) + " " + msg; }
};
//-------------------------------------------------------
ostream& operator << (ostream& out, const Command& c);
//-------------------------------------------------------
