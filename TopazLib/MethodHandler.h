#pragma once

#include "Command.h"
#include "CallBack.h"

class VirtualMachine;
class Command;

//-------------------------------------------------------
// this class encapsulates a Method handler
//-------------------------------------------------------
class MethodHandler
{
public:
	virtual void run(VirtualMachine& vm) = 0;
};
//-------------------------------------------------------
// this class encapsulates a Method handler
//-------------------------------------------------------
class NativeMethodHandler : public MethodHandler
{
public:
	NativeMethodHandler(CallBack* handler) : mHandler(handler) {}
	void run(VirtualMachine& vm) override { mHandler->run(&vm); }
private:
	CallBack* mHandler;
};
//-------------------------------------------------------
class CompiledMethodHandler : public MethodHandler
{
public:
	void addCmd(Command* cmd) { mCmds.push_back(cmd); }
	void run(VirtualMachine& vm) override;
private:
	vector<Command*> mCmds;
};
//-------------------------------------------------------
