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
	virtual bool run(VirtualMachine& vm, int& pc) = 0;
	Symbol* mArg[3];
	int mLine;
protected:
	void error(const string& msg) { throw string("line ") + to_string(mLine) + " " + msg; }
};
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, const Command& c)
{
	out << c.name();
	for (int i = 0; i < 3; i++)
		if (c.mArg[i])
			out << " " << c.mArg[i]->id << " ";
}
//-------------------------------------------------------
