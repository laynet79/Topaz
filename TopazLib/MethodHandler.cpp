#include "MethodHandler.h"
#include "Command.h"

//-------------------------------------------------------
void CompiledMethodHandler::run(VirtualMachine& vm)
{
	int pc = 0;
	while (mCmds[pc]->run(vm, pc));
}
//-------------------------------------------------------
