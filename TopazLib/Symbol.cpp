#include "Symbol.h"
#include "VirtualMachine.h"
#include "Class.h"

//-------------------------------------------------------
int Constant::sNextId = 100;
int Variable::sNextClassId = 100;
int Variable::sNextInstId  = 100;
int Variable::sNextParamId = 100;
int Variable::sNextLocalId = 100;
int Variable::sNextTempId  = 100;
//-------------------------------------------------------
Value*& Symbol::value(VirtualMachine& vm)
{
	switch (kind)
	{
	case STATIC:
		return ((Class*)parent)->classVar(address);
	case INSTANCE:
		return (*vm.stack().inst())[address];
	case PARAM:
		return vm.stack().param(address);
	case LOCAL:
		return vm.stack().local(address);
	case CONSTANT:
		return vm.constant(address);
	default:
		throw "value requested for non-value type";
	}
}
//-------------------------------------------------------
