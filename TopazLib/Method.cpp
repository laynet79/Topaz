#include "Method.h"
#include "MethodHandler.h"

//-------------------------------------------------------
int Method::sNextId = 100;
//-------------------------------------------------------
Method::Method(Symbol* c, const string& name, Access access, MethodHandler* handler)
	: Symbol((Symbol*)c, name, METHOD, nextId(), access), mLocalCnt(0), mHandler(handler)
{
	// create a global string constant using the method name that will
	// be used a key to lookup methods of this name
	mSelector = this->add(name, GLOBAL);
}
//-------------------------------------------------------
Symbol* Method::create(const string& name, Kind kind)
{
	Variable* v = new Variable(this, name, kind);
	switch (v->kind)
	{
	case PARAM:
		{
			v->address = (int)mParams.size();
			mParams.push_back(v);
		}
	case LOCAL:
		{
			v->address = (int)mLocals.size();
			mLocals.push_back(v);
		}
	case TEMP:
		{
			v->address = (int)mTemps.size();
			mTemps.push_back(v);
		}
	default:
		return nullptr;
	}
	return v;
}
//-------------------------------------------------------
void Method::link()
{
	for (Variable* t : mTemps)
		t->address += (int)mLocals.size();
	mLocalCnt = (int)(mLocals.size() + mTemps.size());
}
//-------------------------------------------------------
void Method::run(VirtualMachine& vm)
{
	return mHandler->run(vm);
}
//-------------------------------------------------------

