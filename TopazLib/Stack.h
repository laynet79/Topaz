#pragma once
#include "Value.h"
#include "Collection.h"

//-------------------------------------------------------
// This class implements the run-time stack of the Topaz
// virtual machine
//-------------------------------------------------------
class Stack
{
public:
	Stack()
	{
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
		mTos -= cnt;
	}
	Value pop()
	{
		return mStack[--mTos];
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

