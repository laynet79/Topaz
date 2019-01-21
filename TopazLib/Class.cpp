#include "Collection.h"
#include "Class.h"
#include "Method.h"

//-------------------------------------------------------
int Class::sNextId = 100;
//-------------------------------------------------------
void Class::run(VirtualMachine& vm)
{
	mMain->run(vm);
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
			v->address = (int)mClassVars.size();
			mClassVars.push_back(v);
			return v;
		}
		else
		{
			v->address = (int)mInstanceVars.size();
			mInstanceVars.push_back(v);
			return v;
		}
	}
	case METHOD:
	{
		Method* m = new Method(this, name, access, nullptr);
		mMethods[m->selector()] = m;
		if (m->name == "Main")
			mMain = m;
		return m;
	}
	default:
		return nullptr;
	}
}
//-------------------------------------------------------
Instance* Class::createInstance() { return new Instance(this); }
//-------------------------------------------------------

