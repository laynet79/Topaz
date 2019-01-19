#include "Symbol.h"
#include "VirtualMachine.h"
#include "Class.h"

//-------------------------------------------------------
Value& Symbol::value(VirtualMachine& vm)
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
