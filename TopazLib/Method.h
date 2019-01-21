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
	Method(Symbol* c, const string& name, Access access, MethodHandler* handler);

	static void resetId() { sNextId = 100; }

	Symbol* create(const string& name, Kind kind) override;

	void link();

	Symbol* selector() { return mSelector; }
	int paramCnt() { return (int)mParams.size(); }
	int localCnt() { return mLocalCnt; }

	void run(VirtualMachine& vm);

protected:
	Symbol*				mSelector;
	vector<Variable*>	mParams;
	vector<Variable*>	mLocals;
	vector<Variable*>	mTemps;
	MethodHandler*		mHandler;
	int					mLocalCnt;

	static int sNextId;
	static string nextId(bool reset = false)
	{
		string s = "F" + to_string(sNextId++);
		return s;
	}
};
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, const Method& m)
{
	return out;
}
//-------------------------------------------------------
