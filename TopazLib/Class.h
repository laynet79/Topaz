#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "Symbol.h"

class Instance;
class Method;
class Environment;
class VirtualMachine;

//-------------------------------------------------------
// this class represents a Topaz class
//-------------------------------------------------------
class Class : public Symbol
{
public:
	Class(Symbol* parent, const string& name)
		: Symbol(parent, name, CLASS, nextId(), PUBLIC), mNullInst(this, 0), mMain(nullptr)
	{
		mNullInst.deref();
	}

	Symbol* create(const string& name, Kind kind) override;

	void reset();

	static void resetId() { sNextId = 100; }

	Instance* nullInstance() { return &mNullInst; }

	int size() { return (int)mInstanceVars.size(); }
	Value*& classVar(int i) { return mClassVars[i]->value(); }

	void run(VirtualMachine& vm);

	Instance* createInstance();

	Method* lookupMethod(const string& name) { return mMethodsByName.at(name); }
	Method* lookupMethod(Symbol* selector)   { return mMethods.at(selector);   }

private:
	Instance			 mNullInst;
	vector<Method*>		 mClassMethods;
	map<Symbol*, Method*>mMethods;
	map<string, Method*> mMethodsByName;
	vector<Variable*>	 mClassVars;
	vector<Variable*>    mInstanceVars;
	Method*				 mMain;

	static int sNextId;
	static string nextId()
	{
		string s = "C" + to_string(sNextId++);
		return s;
	}
};
