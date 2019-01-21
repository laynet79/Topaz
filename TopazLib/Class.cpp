#include "Collection.h"
#include "Class.h"
#include "Method.h"

//-------------------------------------------------------
void Class::run(VirtualMachine& vm)
{
	mMain->run(vm);
}
//-------------------------------------------------------
Symbol* Class::create(const string& name, Kind kind, Access access, bool isStatic)
{
	switch (kind)
	{
	case STATIC:
	{
		ClassVar* c = new ClassVar(this, name, access);
		c->address = (int)mClassVars.size();
		mClassVars.push_back(c);
		return c;
	}
	case INSTANCE:
	{
		InstanceVar* i = new InstanceVar(this, name, access);
		i->address = (int)mClassVars.size();
		mInstanceVars.push_back(i);
		return i;
	}
	case METHOD:
	{
		Method* m = new Method(this, name, access, nullptr);
		mMethods[m->selector()] = m;
		return m;
	}
	default:
		return nullptr;
	}
}
//-------------------------------------------------------
Instance* Class::createInstance() { return new Instance(this); }
//-------------------------------------------------------

