#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Symbol.h"

class Instance;
class Method;
class Environment;
class VirtualMachine;

//-------------------------------------------------------
// this class represents a class
//-------------------------------------------------------
class Class : public Symbol
{
public:
	Class(Symbol* parent, const string& name) : Symbol(parent, name, CLASS, nextId(), PUBLIC), mMain(nullptr) {}

	Symbol* create(const string& name, Kind kind, Access access = PROTECTED, bool isStatic = false) override;

	void reset()
	{
		for (ClassVar* v : mClassVars)
			v->value() = Value(0);
	}

	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "C" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}

	int size() { return (int)mInstanceVars.size(); }
	Value& classVar(int i) { return mClassVars[i]->value(); }

	void run(VirtualMachine& vm);

	Instance* createInstance();



	void addMethod(Method* method, bool isStatic, bool isMain = false);
	void addVariable(Variable* v, bool isStatic);

private:
	vector<Method*>		 mClassMethods;
	vector<Method*>		 mMethods;
	vector<ClassVar*>	 mClassVars;
	vector<InstanceVar*> mInstanceVars;
	Method*				 mMain;
};