#pragma once
#include "Value.h"
#include "Collection.h"

//-------------------------------------------------------
// This class implements the run-time stack of the Topaz
// virtual machine.  A typical stack frame is shown below,
// growing down (stack addresses increase downward). Notice
// that parameters are pushed on the stack in the order they
// appear in the function call to simply the compiler. This
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
		mTos = mFrame = 0;
	}

	void reset()
	{
		// release all stack owned reference values
		for (int i = 0; i < STACK_SIZE; i++)
			mStack[i] = Value();
		mTos = mFrame = 0;
	}

	void push(const Value& value)
	{
		if (mTos == STACK_SIZE)
			throw "stack overflow";
		mStack[mTos++] = value;
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
			mStack[--mTos] = Value(); // free any reference values
	}
	Value pop()
	{
		Value v = mStack[--mTos];
		mStack[mTos] = Value(); // free any reference values
		return v;
	}
	void newFrame(Instance* inst, int paramCnt, int localCnt)
	{
		int prevFrame = mFrame;
		mFrame = mTos;
		push(prevFrame);
		push(paramCnt);
		push(inst);
		reserve(localCnt);
	}
	void popFrame()
	{
		mTos = mFrame;
		mFrame = mStack[mFrame].index();
	}
	Instance* inst()
	{
		return (Instance*)mStack[mFrame + 2].object();
	}
	Value& param(int i)
	{
		return mStack[mFrame - mStack[mFrame+1].index() + i];
	}
	Value& local(int i)
	{
		return mStack[mFrame + i + 3];
	}
	
private:
	static const int STACK_SIZE = 65536;
	int mTos;
	int mFrame;
	Value mStack[STACK_SIZE];
};

