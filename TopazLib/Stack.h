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
//	|		param 0		| 0
//	+-------------------+
//	|		...			| 1
//	+-------------------+
//	|		param n		| 2
//	+-------------------+
//	|	previous FP		| 3	<--- FP (frame pointer)
//	+-------------------+
//	|	param Cnt		| 4
//	+-------------------+
//	|	this pointer	| 5
//	+-------------------+
//	|		local 0		| 6
//	+-------------------+
//	|		...			| 7
//	+-------------------+
//	|		local n		| 8
//	+-------------------+
//	|					| 9	<--- TOS (top of stack)
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
			Value::set(mStack[i], nullptr);
		mTos = mFrame = 0;
		push(Value::number(0.0));
		push(Value::number(0.0));
	}

	void push(int v) { push(Value::number(v)); }
	int stackInt(int n) { return mStack[n]->integer(); }

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
			Value::set(mStack[--mTos], nullptr);
	}
	Value* pop()
	{
		Value* v = nullptr;
		Value::set(v, mStack[--mTos]);
		Value::set(mStack[mTos], nullptr);
		return v;
	}
	void newFrame(Value* inst, int paramCnt, int localCnt)
	{
		int prevFrame = mFrame;
		mFrame = mTos;
		push(prevFrame);
		push(paramCnt);
		push(inst);
		reserve(localCnt);
		mParamCnt = paramCnt;
	}
	void popFrame(Value* rtn)
	{
		int prevFrame = stackInt(mFrame);
		int popCnt = mTos - mFrame + mParamCnt;
		pop(popCnt);
		mFrame = prevFrame;
		mParamCnt = stackInt(mFrame+1);
		push(rtn);
	}
	Instance* inst()
	{
		return (Instance*)mStack[mFrame + 2];
	}

	int paramCnt() { return mParamCnt; }

	Value*& param(int i)
	{
		if (i < 0 || i >= mParamCnt)
			throw "parameter does not exist";
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
	int mParamCnt = 0;
	Value* mStack[STACK_SIZE] = { nullptr };
};

