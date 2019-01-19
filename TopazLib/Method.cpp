#include "Method.h"
#include "MethodHandler.h"

//-------------------------------------------------------
Symbol* Method::create(const string& name, Kind kind, Access access, bool isStatic)
{
	switch (kind)
	{
	case PARAM:
		{
			Parameter* s = new Parameter(this, name);
			s->address = (int)mParams.size();
			mParams.push_back(s);
			return s;
		}
	case LOCAL:
		{
			Local* s = new Local(this, name);
			s->address = (int)mLocals.size();
			mLocals.push_back(s);
			return s;
		}
	case TEMP:
		{
			Temporary* s = new Temporary(this, name);
			s->address = (int)mTemps.size();
			mTemps.push_back(s);
			return s;
		}
	default:
		return nullptr;
		break;
	}
}
//-------------------------------------------------------
void Method::link()
{
	for (Temporary* t : mTemps)
		t->address += (int)mLocals.size();
	mLocalCnt = (int)(mLocals.size() + mTemps.size());
}
//-------------------------------------------------------
void Method::run(VirtualMachine& vm)
{
	return mHandler->run(vm);
}
//-------------------------------------------------------

