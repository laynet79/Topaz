#pragma once
#include "Value.h"

//-------------------------------------------------------
// This class implements the run-time stack of the Topaz
// virtual machine.  A typical stack frame is shown below,
// growing down (stack addresses increase downward). Notice
// that parameters are pushed on the stack in the order they
// appear in the function call to simplify the compiler
// (parameters are pushed onto the stack in the order encountered
// which makes them backward relative to the frame pointer). This
// required a parameter count be added to the stack so that
// parameters can be indexed correctly relative to the
// frame pointer.
//
//	|					|
//	+-------------------+
//	|		param 0		|
//	+-------------------+
//	|		...			|
//	+-------------------+
//	|		param n		|
//	+-------------------+
//	|	previous FP		|	<--- FP (frame pointer)
//	+-------------------+
//	|	param Cnt		|
//	+-------------------+
//	|	this pointer	|
//	+-------------------+
//	|		local 0		|
//	+-------------------+
//	|		...			|
//	+-------------------+
//	|		local n		|
//	+-------------------+
//	|					|	<--- TOS (top of stack)
//
//-------------------------------------------------------
class Stack
{
public:
	Stack()
	{
		reset();
	}

	void reset()
	{
		// release all stack owned reference values
		for (int i = 0; i < STACK_SIZE; i++)
			Value::set(mStack[i], Null::value());
		mTos = mFrame = 0;
	}

	void push(Value* value)
	{
		if (mTos == STACK_SIZE)
			throw "stack overflow";
		Value::set(mStack[mTos++], value);
	}
	void reserve(int cnt)
	{
		if ((mTos + cnt) >= STACK_SIZE)
			throw "stack overflow";
		mTos += cnt;
	}
	void pop(int cnt)
	{
		for (int i = 0; i < cnt; i++)
			Value::set(mStack[--mTos], Null::value());
	}
	Value* pop()
	{
		Value* v;
		Value::set(v, mStack[--mTos]);
		Value::set(mStack[mTos], Null::value());
		return v;
	}
	void newFrame(Instance* inst, int paramCnt, int localCnt)
	{
		int prevFrame = mFrame;
		mFrame = mTos;
		push(Value::number(prevFrame));
		push(Value::number(paramCnt));
		push((Value*)inst);
		reserve(localCnt);
	}
	void popFrame()
	{
		mTos = mFrame;
		mFrame = ((Number*)mStack[mFrame])->intValue();
	}
	Instance* inst()
	{
		return (Instance*)mStack[mFrame + 2];
	}
	Value*& param(int i)
	{
		return mStack[mFrame - ((Number*)mStack[mFrame+1])->intValue() + i];
	}
	Value*& local(int i)
	{
		return mStack[mFrame + i + 3];
	}
	
private:
	static const int STACK_SIZE = 65536;
	int mTos = 0;
	int mFrame = 0;
	Value* mStack[STACK_SIZE] = { nullptr };
};

