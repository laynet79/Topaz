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
	Symbol* s;
	switch (kind)
	{
	case STATIC:
	{
		s = new ClassVar(this, name, access);
		s->address = (int)mClassVars.size();
		mClassVars.push_back((ClassVar*)s);
		break;
	}
	case INSTANCE:
	{
		s = new InstanceVar(this, name, access);
		s->address = (int)mClassVars.size();
		mInstanceVars.push_back((InstanceVar*)s);
		break;
	}
	case METHOD:
	{
		s = new Method(this, name, access, nullptr);
		s->address = (int)mMethods.size();
		mMethods.push_back((Method*)s);
		break;
	}
	default:
		s = nullptr;
	}
	return s;
}
//-------------------------------------------------------
Instance* Class::createInstance() { return new Instance(this); }
//-------------------------------------------------------
void Class::addMethod(Method* method, bool isStatic, bool isMain)
{
	if (isStatic)
	{
		method->address = (int)mClassMethods.size();
		mClassMethods.push_back(method);
		if (isMain)
			mMain = method;
	}
	else
	{
		method->address = (int)mMethods.size();
		mMethods.push_back(method);
	}
}
//-------------------------------------------------------
void Class::addVariable(Variable* v, bool isStatic)
{
	if (isStatic)
	{
		v->address = (int)mClassVars.size();
		mClassVars.push_back((ClassVar*)v);
	}
	else
	{
		v->address = (int)mInstanceVars.size();
		mInstanceVars.push_back((InstanceVar*)v);
	}
}
//-------------------------------------------------------

