#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Symbol.h"

class Class;
class MethodHandler;

//-------------------------------------------------------
// this class represents a class method
//-------------------------------------------------------
class Method : public Symbol
{
public:
	Method(Symbol* c, const string& name, Access access, MethodHandler* handler)
		: Symbol((Symbol*)c, name, METHOD, nextId(), access), mLocalCnt(0), mHandler(handler) {}

	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "F" + to_string(nextId++);
		if (reset) { nextId = 100; }
		return s;
	}

	Symbol* create(const string& name, Kind kind, Access access = PROTECTED, bool isStatic = false) override;

	void link();

	int paramCnt() { return (int)mParams.size(); }
	int localCnt() { return mLocalCnt; }

	void run(VirtualMachine& vm);

protected:
	vector<Parameter*> mParams;
	vector<Local*>     mLocals;
	vector<Temporary*> mTemps;
	MethodHandler*     mHandler;
	int                mLocalCnt;
};
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, const Method& m)
{
	return out;
}
//-------------------------------------------------------
