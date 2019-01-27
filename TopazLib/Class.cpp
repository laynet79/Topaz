#include "Class.h"
#include "Method.h"
#include <algorithm>

//-------------------------------------------------------
int Class::sNextId = 100;
//-------------------------------------------------------
void Class::run(VirtualMachine& vm)
{
	mMain->run(vm);
}
//-------------------------------------------------------
void Class::reset()
{
	for (Variable* v : mClassVars)
		Value::set(v->value(), (Value*)nullptr);
}
//-------------------------------------------------------
Symbol* Class::create(const string& name, Kind kind)
{
	switch (kind)
	{
	case MEMBER:
	{
		Variable* v = new Variable(this, name, kind);
		if (v->kind == STATIC)
		{
			if (find(mClassVars.begin(), mClassVars.end(), v) != mClassVars.end())
			{
				delete v;
				throw (string("variable already exists: ") + name).c_str();
			}
			v->address = (int)mClassVars.size();
			mClassVars.push_back(v);
			return v;
		}
		else
		{
			if (find(mInstanceVars.begin(), mInstanceVars.end(), v) != mInstanceVars.end())
			{
				delete v;
				throw (string("variable already exists: ") + name).c_str();
			}
			v->address = (int)mInstanceVars.size();
			mInstanceVars.push_back(v);
			return v;
		}
	}
	case METHOD:
	{
		Method* m = new Method(this, name, access, nullptr);
		if (mMethods.find(m->selector()) != mMethods.end())
		{
			delete m;
				throw (string("variable already exists: ") + name).c_str();
		}
		mMethods[m->selector()] = m;
		mMethodsByName[name] = m;
		if (m->name == "Main")
			mMain = m;
		return m;
	}
	default:
		return nullptr;
	}
}
//-------------------------------------------------------
Instance* Class::createInstance() { return new Instance(this, (int)mInstanceVars.size()); }
//-------------------------------------------------------

