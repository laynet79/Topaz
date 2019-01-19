#include "VirtualMachine.h"
#include "Symbol.h"

//-------------------------------------------------------
VirtualMachine::VirtualMachine(vector<Class*>& classes, vector<Constant*>& constants)
	: mClasses(classes), mConstants(constants)
{
}
//-------------------------------------------------------
VirtualMachine::~VirtualMachine()
{
}
//-------------------------------------------------------
Value& VirtualMachine::constant(int index) { Constant* c = mConstants[index]; return c->value(); }
